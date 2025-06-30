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
// fs_err_t get_error();
#if defined(USE_ESP8266)
  FileInterface(SdfsHost *host, std::string path, std::string mode);
#else
  FileInterface(std::string, std::string mode);
#endif
  ~FileInterface();

  bool close();
  bool seek(size_t pos);
  bool flush();
  int read(void *buf, size_t);
  size_t write(void *buf, size_t);
  char get();
  bool put(char);
  // void putback();
  fptr *get_fptr();
  std::string get_path();
  std::string get_name();
  size_t get_size();
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
  FileInfo *get_next();
  bool is_eof();
  fsys_t *get_fs() { return fs; };
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
   *  Save lnk to Host object.
   *  Extract FileSystem object.
   *
   * @param host
   */
  FsInterface(SdfsHost *host);

  // FsInterface(std::string mp) : mount_point(mp) {};
  // //void set_mountpoint(std::string p) { mount_point = p; }
  // #endif

  /**
   * @brief Check is path is correct. Is file or directory exist.
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
   *  r - for read,
   *  w - create and write from beining,
   *  a - for append to the end of file
   * @return FileInterface*
   */
  FileInterface *open_file(std::string path, std::string mode);

  /**
   * @brief   Check is file system initialized and ready to serv
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