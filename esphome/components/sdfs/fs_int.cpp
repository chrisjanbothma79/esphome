#if !defined(USE_ESP8266)
#include "sdfs.h"
#include "fs_interface.h"
namespace esphome {
namespace sdfs {

extern const char *fat_type2str[];
extern const char *fs_err2str[];
extern const char *host_st2str[];

// extern const char *fs_err2str[];
static const char *TAG = "fs_int";
//------------------------------------------------------------------
//   FsInterface methods
//------------------------------------------------------------------

FsInterface::FsInterface(SdfsHost *host) : host_(host) {
  if (host_->get_drv() == NULL) {
    ESP_LOGE(TAG, "SdfsDriver not initialized.");
    last_err_ = FR_INT_ERR;
  }
  fs_ = host_->get_drv()->get_fs();
}

/***********************************************************************
 *
 * @brief Build full path to file or directory.  Include mount point and cur directory path
 *
 * @param path relative or absolute path
 * @return std::string
 */

/***********************************************************************
 * @brief  Check if class initialization complete
 *
 * @return true
 * @return false
 */
bool FsInterface::is_ready() {
  bool is_fs = true;
#if defined(USE_ESP8266)
  is_fs = vol != NULL;
#endif
  is_fs = fs_ != NULL;
  if (!is_fs) {
    last_err_ = FR_INT_ERR;
  }
  return is_fs;
}

/***********************************************************************
 * @brief  Check if file directory exist.
 *
 * @param path relative or absolute path
 * @return true
 * @return false
 */
bool FsInterface::is_exist(const std::string &path) {
  FRESULT rc;
  if (!is_ready())
    return false;

  if (this->is_dir(path)) {
    return true;
  }
  finfo info;
  rc = f_stat(path.c_str(), &info);
  // rc = f_open(&fp,cur_path.c_str(),FA_READ);
  // f_close(&fp);

  return rc == FR_OK;
}

/***********************************************************************
 * @brief   Check if path pint to directory
 *
 * @param path
 * @return true
 * @return false
 */
bool FsInterface::is_dir(const std::string &path) {
  finfo info;
  last_err_ = f_stat(path.c_str(), &info);
  return last_err_ == FR_OK && (info.fattrib & AM_DIR);
}

/***********************************************************************
 * @brief Create directory with pointed file
 *
 * @param name
 * @return true
 * @return false
 */
bool FsInterface::mkdir(const std::string &path) {
  FRESULT rc = f_mkdir(path.c_str());
  return rc == FR_OK;
}

/***********************************************************************
 * @brief  Return size of pointed file
 *
 * @param name
 * @return size_t
 */
// size_t FsInterface::size(std::string path) {
//   finfo info;
//   last_err_ = f_stat(build_path(path).c_str(),&info);
//   return info.fsize;
// }

/***********************************************************************
 * @brief remove directory by path
 *
 * @param path
 * @return true
 * @return false
 */
bool FsInterface::rmdir(const std::string &path) {
  if (!is_dir(path)) {
    return f_rmdir(path.c_str()) == 0;
  }
  return false;
}

/***********************************************************************
 * @brief  rename file or path
 *
 * @param from
 * @param to
 * @return true if sucess
 * @return false eny error (see last_err_or)
 */
bool rename(const std::string &from, const std::string &to) {
  FRESULT rc = f_rename(from.c_str(), to.c_str());
  return rc = FR_OK;
}

/***********************************************************************
 * @brief   Retrun directory files iterator
 *
 * @return FsIterator
 */
FsIterator *FsInterface::list(const std::string &path) { return new FsIterator(host_, path); }

FileInterface *FsInterface::open_file(std::string path, char mode) {
  FileInterface *file = NULL;
  if (is_ready()) {
    file = new FileInterface(path, mode);
  }
  return file;
}

//------------------------------------------------------------------
//   FileInterfce methods
//------------------------------------------------------------------
/**
 * @brief Construct a new File Interface:: File Interface object
 *
 * @param path absolute path, including mount point
 * @param mode 'r' open read only, 'a' open for append, 'w' open for write
 */
FileInterface::FileInterface(std::string path, char mode) : path_(path) {
  switch (mode) {
    case 't':
      open_flag_ = FA_WRITE | FA_CREATE_ALWAYS | FA_CREATE_NEW | FA_OPEN_ALWAYS;
      truncate_ = true;
    case 'w':
      open_flag_ = FA_WRITE | FA_CREATE_ALWAYS | FA_CREATE_NEW | FA_OPEN_ALWAYS;
      break;
    case 'a':
      open_flag_ = FA_WRITE | FA_CREATE_ALWAYS | FA_CREATE_NEW | FA_OPEN_ALWAYS | FA_OPEN_APPEND;
      break;
    case 'r':
      open_flag_ = FA_READ;
      break;
    default:
      last_err_ = FR_INVALID_PARAMETER;
      return;
  }

  last_err_ = f_stat(path_.c_str(), &sys_f_info_);
  last_err_ = f_open(&fp_, path_.c_str(), open_flag_);
  if (last_err_ != FR_OK) {
    ESP_LOGD(TAG, "File open error, %s", fs_err2str[last_err_]);
    f_close(&fp_);
  }
}

/**********************************************************************
 * @brief Destroy the File Interface:: File Interface object
 *
 */
FileInterface::~FileInterface() { f_close(&fp_); }

/**********************************************************************
 * @brief Close file
 *
 * @return true
 * @return false
 */
bool FileInterface::close() {
  last_err_ = f_close(&fp_);
  return last_err_ == FR_OK;
}

/**********************************************************************
 * @brief Read file to buffer
 *
 * @param buf
 * @param sz
 * @return size_t return read bytes. 0 if end of file. -1 if error
 */
int FileInterface::read(void *buf, size_t size) {
  size_t read = -1;
  if (open_flag_ & FA_READ) {
    if (!f_eof(&fp_)) {
      last_err_ = f_read(&fp_, buf, size, &read);
    }

    if (last_err_ != FR_OK) {
      read = -1;
      ESP_LOGV(TAG, "File write error, %s", fs_err2str[last_err_]);
    } else if (f_eof(&fp_)) {
      read = 0;
    }
  }
  return read;
}

/**********************************************************************
 * @brief Write buffer to file from at the current position.
 * if file open as append ('a'), buffer will append to end of file.
 * If open just for write ('w') front from begin of file.
 * Current possition can be movet with seek comend.
 *
 * @param buf
 * @param size
 * @return size_t  number od write bytes.
 */
size_t FileInterface::write(void *buf, size_t size) {
  size_t write = 0;
  if (open_flag_ & FA_OPEN_APPEND) {
    last_err_ = f_lseek(&fp_, f_size(&fp_));
  }
  if (last_err_ == FR_OK) {
    last_err_ = f_write(&fp_, buf, size, &write);
    if ((truncate_) && (last_err_ == FR_OK)) {
      last_err_ = f_truncate(&fp_);
    }
  }
  if (last_err_ != FR_OK) {
    ESP_LOGV(TAG, "File write error, %s", fs_err2str[last_err_]);
  }
  return write;
}

/**********************************************************************
 * @brief set current write position
 *
 * @param pos
 * @return true
 * @return false
 */
bool FileInterface::seek(size_t pos) {
  last_err_ = f_lseek(&fp_, pos);
  return last_err_ == FR_OK;
}

/**********************************************************************
 * @brief  Save current write cache to file
 *
 * @return true
 * @return false
 */
bool FileInterface::flush() {
  last_err_ = f_sync(&fp_);
  return last_err_ == FR_OK;
}

/**********************************************************************
 * @brief  Write  shar to file at current write position (see write)
 *
 * @param c
 */
bool FileInterface::put(char c) { return f_putc(c, &fp_) > -1; }

/**********************************************************************
 * @brief Retrun file pointer for extended fiel operation
 *
 * @return fptr*
 */
fptr *FileInterface::get_fptr() { return &fp_; }
/**********************************************************************
 * @brief  Return file path
 *
 * @return std::string
 */
std::string FileInterface::get_path() { return path_; }

/**********************************************************************
 * @brief get file name
 *
 * @return std::string
 */
std::string FileInterface::get_name() {
  last_err_ = f_stat(path_.c_str(), &sys_f_info_);
  return std::string(sys_f_info_.fname);
}

/**********************************************************************
 * @brief  get file size
 *
 * @return size_t
 */
size_t FileInterface::get_size() {
  last_err_ = f_stat(path_.c_str(), &sys_f_info_);
  return sys_f_info_.fsize;
}

//------------------------------------------------------------------
//   FsIterator methods
//------------------------------------------------------------------

FsIterator::FsIterator(SdfsHost *host, std::string path) : host_(host), path_(path) {
  last_err_ = f_opendir(&dp_, path_.c_str());
}
FsIterator::~FsIterator() { last_err_ = f_closedir(&dp_); }

SdFileInfo *FsIterator::get_next() {
  finfo info;
  last_err_ = f_readdir(&dp_, &info);
  if (last_err_ != FR_OK || info.fname[0] == 0) {
    return NULL;  // End of dir list
  }
  // FileInfo fi;
  sd_file_info_.name = std::string(info.fname);
  sd_file_info_.path = path_;
  sd_file_info_.is_dir = info.fattrib & AM_DIR;
  sd_file_info_.is_hidden = info.fattrib & AM_HID;
  sd_file_info_.is_system = info.fattrib & AM_SYS;
  sd_file_info_.size = info.fsize;
  return &sd_file_info_;
}

}  // namespace sdfs
}  // namespace esphome
#endif
