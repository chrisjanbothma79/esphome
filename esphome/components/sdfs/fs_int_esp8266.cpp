#if defined(USE_ESP8266)
#include "fs_interface.h"
#include "FsLib/FsVolume.h"
#include "esphome/core/log.h"

namespace esphome {
namespace sdfs {

extern const char *fs_err2str[];
static const char *TAG = "fs_int_esp8266";

//------------------------------------------------------------------
//   FileInterface methods
//------------------------------------------------------------------
FileInterface::FileInterface(SdfsHost *host, std::string path, char mode) : path(path) {
  switch (mode) {
    case 't':
      open_flag = O_WRITE | O_CREAT | O_TRUNC;
      truncate = true;
    case 'w':
      open_flag = O_WRITE | O_CREAT;
      break;
    case 'a':
      open_flag = O_AT_END | O_APPEND | O_WRITE;
      break;
    case 'r':
      open_flag = O_READ;
      break;
    default:
      last_err = FR_INVALID_PARAMETER;
      return;
  }

  fs = host->get_drv()->get_fs();
  if (fs == NULL) {
    last_err = FR_NO_FILESYSTEM;
    return;
  }
  fp = fs->open(path.c_str(), open_flag);
  last_err = fp.getError();
}

FileInterface::~FileInterface() {
  if (last_err == FR_OK)
    fp.close();
}

bool FileInterface::close() {
  if (last_err != FR_OK)
    return false;
  return fp.close();
}
bool FileInterface::seek(size_t pos) {
  if (last_err != FR_OK)
    return false;
  return fp.seek(pos);
}
bool FileInterface::flush() {
  if (last_err != FR_OK)
    return false;
  fp.flush();
  return true;
}
int FileInterface::read(void *buf, size_t sz) {
  if (last_err != FR_OK)
    return -1;
  int rd = fp.read(buf, sz);
  if (rd < 0) {
    last_err = fp.getError();
  }
  return rd;
}

size_t FileInterface::write(void *buf, size_t sz) {
  if (last_err != FR_OK)
    return 0;
  size_t wr = fp.write(buf, sz);
  if (wr <= 0) {
    // last_err = fp.getError();
    last_err = FR_DISK_ERR;
  }
  return wr;
}

char FileInterface::get() {
  if (last_err != FR_OK)
    return 0;
  uint8_t rd = fp.read();
  if (rd < 0) {
    last_err = fp.getError();
  }
  return rd;
}

bool FileInterface::put(char ch) {
  if (last_err != FR_OK)
    return false;
  uint8_t wr = fp.write(ch);
  if (wr < 1) {
    last_err = fp.getError();
  }
  return wr > 0;
}
// void putback();
fptr *FileInterface::get_fptr() {
  if (last_err != FR_OK)
    return NULL;
  return &fp;
}

std::string FileInterface::get_path() { return path; }

std::string FileInterface::get_name() {
  if (last_err != FR_OK)
    return std::string("");

#if defined(USE_UTF8_LONG_NAMES) || defined(USE_LONG_FILE_NAMES)
  char fname[255];
  uint8_t len = 255;
#else
  cher fname[12];
  uint8_t len = 12;
#endif
  size_t nlen = fp.getName(fname, len);
  return std::string(fname, nlen);
}

size_t FileInterface::get_size() {
  if (last_err != FR_OK)
    return -1;
  return fp.size();
}

//------------------------------------------------------------------
//   FsIterator methods
//------------------------------------------------------------------

FsIterator::FsIterator(SdfsHost *host, std::string path) : path(path), host(host) {
  fs = host->get_drv()->get_fs();
  dp = fs->open(path.c_str(), O_RDONLY);
}

FsIterator::~FsIterator() { dp.close(); }

FileInfo *FsIterator::get_next() {
  dptr next_dir;
  if (dp.openNext(&next_dir, O_RDONLY)) {
#if defined(USE_UTF8_LONG_NAMES) || defined(USE_LONG_FILE_NAMES)
    char fname[255];
    uint8_t len = 255;
#else
    cher fname[12];
    uint8_t len = 12;
#endif

    // FileInfo info;
    fi.is_dir = next_dir.isDir();
    fi.is_hidden = next_dir.isHidden();
    fi.is_system = false;
    fi.size = 0;
    size_t flen = next_dir.getName(fname, len);
    std::string fn = std::string(fname, flen);
    fi.name = fn;
    fi.path = path + "/" + fn;
    return &fi;
  } else
    eof = true;
  return NULL;
}

bool FsIterator::is_eof() { return eof; }

//------------------------------------------------------------------
//   FsInterface methods
//------------------------------------------------------------------

FsInterface::FsInterface(SdfsHost *h) : host(h) {
  last_err = 0;
  fs = host->get_drv()->get_fs();
  if (host->get_drv()->get_fs() == NULL) {
    last_err = FR_NO_FILESYSTEM;
    ESP_LOGD(TAG, "Filesystem don't init");
  }
};

bool FsInterface::is_exist(std::string path) {
  last_err = 0;
  // fs = host->get_drv()->get_fs();
  FsFile tmpFile;
  bool is_open = tmpFile.open(fs, path.c_str(), O_RDONLY);

  if (is_open) {
    last_err = tmpFile.getError();
    tmpFile.close();
    return last_err == 0 ? true : false;
  }
  return false;
}

bool FsInterface::is_dir(std::string path) {
  bool ret = false;
  last_err = 0;

  FsFile tmpFile;
  bool is_open = tmpFile.open(fs, path.c_str(), O_RDONLY);

  if (is_open) {
    last_err = tmpFile.getError();
    if ((tmpFile.isDir()) && (last_err == 0))
      ret = true;
    tmpFile.close();
  }
  return ret;
}

bool FsInterface::rename(std::string old_path, std::string new_path) {
  return fs->rename(old_path.c_str(), new_path.c_str());
}

bool FsInterface::mkdir(std::string path) { return fs->mkdir(path.c_str()); }

bool FsInterface::rmdir(std::string path) { return fs->rmdir(path.c_str()); }

FsIterator *FsInterface::list(std::string path) {
  FsIterator *iter = NULL;
  if (is_dir(path)) {
    iter = new FsIterator(host, path);
  }
  return iter;
}

FileInterface *FsInterface::open_file(std::string path, char mode) {
  last_err = 0;
  FileInterface *file = NULL;

  if ((!this->is_dir(path)) && (last_err == 0)) {
    file = new FileInterface(host, path, mode);
  }
  return file;
}

}  // namespace sdfs
}  // namespace esphome
#endif