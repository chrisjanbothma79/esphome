#if defined(USE_ESP8266)
#include "sdfs.h"
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
FileInterface::FileInterface(SdfsHost *host, std::string path, char mode) : path_(path) {
  switch (mode) {
    case 't':
      open_flag_ = O_WRITE | O_CREAT | O_TRUNC;
      truncate_ = true;
    case 'w':
      open_flag_ = O_WRITE | O_CREAT;
      break;
    case 'a':
      open_flag_ = O_AT_END | O_APPEND | O_WRITE;
      break;
    case 'r':
      open_flag_ = O_READ;
      break;
    default:
      last_err_ = FR_INVALID_PARAMETER;
      return;
  }
  fs_ = host->get_drv()->get_fs();
  if (fs_ == NULL) {
    last_err_ = FR_NO_FILESYSTEM;
    return;
  }
  fp_ = fs_->open(path.c_str(), open_flag_);
  last_err_ = fp_.getError();
}

FileInterface::~FileInterface() {
  if (last_err_ == FR_OK)
    fp_.close();
}

bool FileInterface::close() {
  if (last_err_ != FR_OK)
    return false;
  return fp_.close();
}
bool FileInterface::seek(size_t pos) {
  if (last_err_ != FR_OK)
    return false;
  return fp_.seek(pos);
}
bool FileInterface::flush() {
  if (last_err_ != FR_OK)
    return false;
  fp_.flush();
  return true;
}
int FileInterface::read(void *buf, size_t size) {
  if (last_err_ != FR_OK)
    return -1;
  int rd = fp_.read(buf, size);
  if (rd < 0) {
    last_err_ = fp_.getError();
  }
  return rd;
}

size_t FileInterface::write(void *buf, size_t size) {
  if (last_err_ != FR_OK)
    return 0;
  size_t wr = fp_.write(buf, size);
  if (wr <= 0) {
    // last_err = fp.getError();
    last_err_ = FR_DISK_ERR;
  }
  return wr;
}

char FileInterface::get() {
  if (last_err_ != FR_OK)
    return 0;
  uint8_t rd = fp_.read();
  if (rd < 0) {
    last_err_ = fp_.getError();
  }
  return rd;
}

bool FileInterface::put(char ch) {
  if (last_err_ != FR_OK)
    return false;
  uint8_t wr = fp_.write(ch);
  if (wr < 1) {
    last_err_ = fp_.getError();
  }
  return wr > 0;
}
// void putback();
fptr *FileInterface::get_fptr() {
  if (last_err_ != FR_OK)
    return NULL;
  return &fp_;
}

std::string FileInterface::get_path() { return path_; }

std::string FileInterface::get_name() {
  if (last_err_ != FR_OK)
    return std::string("");

#if defined(USE_UTF8_LONG_NAMES) || defined(USE_LONG_FILE_NAMES)
  char fname[255];
  uint8_t len = 255;
#else
  cher fname[12];
  uint8_t len = 12;
#endif
  size_t nlen = fp_.getName(fname, len);
  return std::string(fname, nlen);
}

size_t FileInterface::get_size() {
  if (last_err_ != FR_OK)
    return -1;
  return fp_.size();
}

//------------------------------------------------------------------
//   FsIterator methods
//------------------------------------------------------------------

FsIterator::FsIterator(SdfsHost *host, std::string path) : path_(path), host_(host) {
  fs_ = host_->get_drv()->get_fs();
  dp_ = fs_->open(path_.c_str(), O_RDONLY);
}

FsIterator::~FsIterator() { dp_.close(); }

SdFileInfo *FsIterator::get_next() {
  dptr next_dir;
  if (dp_.openNext(&next_dir, O_RDONLY)) {
#if defined(USE_UTF8_LONG_NAMES) || defined(USE_LONG_FILE_NAMES)
    char fname[255];
    uint8_t len = 255;
#else
    cher fname[12];
    uint8_t len = 12;
#endif

    sd_file_into_.is_dir = next_dir.isDir();
    sd_file_into_.is_hidden = next_dir.isHidden();
    sd_file_into_.is_system = false;
    sd_file_into_.size = 0;
    size_t flen = next_dir.getName(fname, len);
    std::string fn = std::string(fname, flen);
    sd_file_into_.name = fn;
    sd_file_into_.path = path_ + "/" + fn;
    return &sd_file_into_;

  } else
    eof_ = true;
  return NULL;
}

bool FsIterator::is_eof() { return eof_; }

//------------------------------------------------------------------
//   FsInterface methods
//------------------------------------------------------------------

FsInterface::FsInterface(SdfsHost *host) : host_(host) {
  last_err_ = 0;
  fs_ = host_->get_drv()->get_fs();
  if (host_->get_drv()->get_fs() == NULL) {
    last_err_ = FR_NO_FILESYSTEM;
    ESP_LOGD(TAG, "Filesystem don't init");
  }
};

bool FsInterface::is_exist(const std::string &path) {
  last_err_ = 0;
  // fs = host->get_drv()->get_fs();
  FsFile tmpFile;
  bool is_open = tmpFile.open(fs_, path.c_str(), O_RDONLY);

  if (is_open) {
    last_err_ = tmpFile.getError();
    tmpFile.close();
    return last_err_ == 0 ? true : false;
  }
  return false;
}

bool FsInterface::is_dir(const std::string &path) {
  bool ret = false;
  last_err_ = 0;

  FsFile tmpFile;
  bool is_open = tmpFile.open(fs_, path.c_str(), O_RDONLY);

  if (is_open) {
    last_err_ = tmpFile.getError();
    if ((tmpFile.isDir()) && (last_err_ == 0))
      ret = true;
    tmpFile.close();
  }
  return ret;
}

bool FsInterface::rename(const std::string &old_path, const std::string &new_path) {
  return fs_->rename(old_path.c_str(), new_path.c_str());
}

bool FsInterface::mkdir(const std::string &path) { return fs_->mkdir(path.c_str()); }

bool FsInterface::rmdir(const std::string &path) { return fs_->rmdir(path.c_str()); }

FsIterator *FsInterface::list(const std::string &path) {
  FsIterator *iter = NULL;
  if (is_dir(path_)) {
    iter = new FsIterator(host_, path);
  }
  return iter;
}

FileInterface *FsInterface::open_file(std::string path, char mode) {
  last_err_ = 0;
  FileInterface *file = NULL;

  if ((!this->is_dir(path)) && (last_err_ == 0)) {
    file = new FileInterface(host_, path, mode);
  }
  return file;
}

}  // namespace sdfs
}  // namespace esphome
#endif
