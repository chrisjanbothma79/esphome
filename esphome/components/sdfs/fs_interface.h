#pragma once
#include "sdfs_defines.h"
#include "sdfs.h"

#if !defined(USE_ESP8266)
#include "ff.h"
#include "dirent.h"
#include "stdio.h"
typedef FIL fptr;
typedef FF_DIR dptr;
typedef FILINFO finfo;
#else
#include "SdFat.h"
// #include "FsLib/FsVolume.h"
// #include "FsLib/FsFile.h"
typedef FsBaseFile fptr;
typedef FsBaseFile dptr;
#endif

namespace esphome {
namespace sdfs {

typedef struct {
  std::string name;
  std::string path;
  size_t size;
  bool exist = false;
  bool is_dir = false;
  bool is_hidden = false;
  bool is_system = false;
  bool is_ro = false;
} FileInfo;

// typedef FRESULT fs_err_t;

//  FatFs Description
// https://elm-chan.org/fsw/ff/00index_e.html
class SdfsHost;

class FileInterface {
 public:
#if defined(USE_ESP8266)
  FileInterface(SdfsHost *host, std::string path, char mode);
#else
  FileInterface(std::string, char mode);
#endif
  ~FileInterface();

  /**
   * @brief   Close file
   *
   * @return true
   * @return false
   */
  bool close();
  /**
   * @brief Set file position for read or write
   *
   * @param pos
   * @return true
   * @return false
   */
  bool seek(size_t pos);

  /**
   * @brief Save cashed data to card
   *
   * @return true
   * @return false
   */
  bool flush();

  /**
   * @brief  Read from file
   *
   * @param buf pointer to memory buffer where read to
   * @param size  Buffer size.
   * @return int  size or rallyr ead bytes. 0 if eof; -1 if error
   */
  int read(void *buf, size_t size);

  /**
   * @brief Write data to file.  At the open  start write to end of file or to begining Depends of open mode
   *  other write  will be after last write position.
   *
   * @param buf Pointer to memory buffer
   * @param size  Buffer size.
   * @return size_t  size or writer bytes. 0 if error
   */
  size_t write(void *buf, size_t size);

  /**
   * @brief Read one byte from file. Read form last read position or from begining if no last position
   *
   * @return char
   */
  char get();
  /**
   * @brief write char to file.
   *
   * @return true
   * @return false
   */
  bool put(char);
  /**
   * @brief  return opened file pointer with type of used framework.
   *
   * @return fptr*
   */
  fptr *get_fptr();
  /**
   * @brief Retrun file path ( w/o file name)
   *
   * @return std::string
   */
  std::string get_path();
  /**
   * @brief Return file name
   *
   * @return std::string
   */
  std::string get_name();
  /**
   * @brief Reterun file size
   *
   * @return size_t
   */
  size_t get_size();
  /**
   * @brief Return erro of last file i/o operation. If Any
   *
   * @return FRESULT
   */
  FRESULT get_error() { return last_err; };

 private:
  bool truncate = false;
  uint8_t open_flag = 0;
  std::string path;
  fsys_t *fs;
  fptr fp;
  FRESULT last_err = FR_OK;
#if !defined(USE_ESP8266)
  finfo info;
#endif
};

class FsInterface;
class FsIterator {
 public:
  FsIterator(SdfsHost *, std::string);
  ~FsIterator();

  /**
   * @brief Return file information  for next file in directory, for witch we open instance of this class.
   *
   * @return FileInfo*
   */
  FileInfo *get_next();

  /**
   * @brief  Whrn there is no vor files in chain.
   *
   * @return true
   * @return false
   */
  bool is_eof();

  /**
   * @brief Return fs object for this directory.
   *
   * @return fsys_t*
   */
  fsys_t *get_fs() { return fs; };

  /**
   * @brief Return error num for lase fs operation.
   *
   * @return FRESULT
   */
  FRESULT get_error() { return last_err; };

 private:
  dptr dp;
  bool eof = false;
  std::string path;
  FRESULT last_err = FR_OK;
  FileInfo fi;
  SdfsHost *host;
  fsys_t *fs;
};

class FsInterface {
 public:
  /**
   * @brief Construct a new Filesystem representation object.
   *
   * @param host
   */
  FsInterface(SdfsHost *host);

  /**
   * @brief Check if path exist.
   *
   * @param path
   * @return true
   * @return false
   */
  bool is_exist(std::string path);

  /**
   * @brief Check if name or path is directory.
   *
   * @param path
   * @return true
   * @return false
   */
  bool is_dir(std::string path);

  /**
   * @brief  Move (rename) path to file or directory
   *
   * @param from  path from
   * @param to  path to
   * @return true
   * @return false
   */
  bool rename(std::string from, std::string to);

  /**
   * @brief  Create directory by its path
   *
   * @param path
   * @return true
   * @return false
   */
  bool mkdir(std::string path);

  /**
   * @brief  Delete directory
   *
   * @param path
   * @return true
   * @return false
   */
  bool rmdir(std::string path);

  /**
   * @brief Return class for iterate through directory objects
   *
   * @param path
   * @return FsIterator*
   */
  FsIterator *list(std::string path);

  /**
   * @brief
   *
   * @param path File path
   * @param mode  file open mode:
   *  'r' - for read,
   *  'w' - create and write from beining,
   *  'a' - for append to the end of file
   *  't' - write and truncae
   * @return FileInterface*
   */
  FileInterface *open_file(std::string path, char mode);

  /**
   * @brief   Check is file system initialized and ready to i/o
   *
   * @return true
   * @return false
   */
  bool is_ready();

 protected:
  FileInfo info;
  // std::string build_path(std::string);
  std::string path = "/";
  std::string mount_point = "";
  // FF_DIR root_object;
  FRESULT last_err = FR_OK;
  bool exist = true;
  SdfsHost *host;
  fsys_t *fs;
};

}  // namespace sdfs
}  // namespace esphome