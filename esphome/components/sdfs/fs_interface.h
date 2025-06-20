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

typedef enum {
  FR_OK = 0,              /* (0) Succeeded */
  FR_DISK_ERR,            /* (1) A hard error occurred in the low level disk I/O layer */
  FR_INT_ERR,             /* (2) Assertion failed */
  FR_NOT_READY,           /* (3) The physical drive cannot work */
  FR_NO_FILE,             /* (4) Could not find the file */
  FR_NO_PATH,             /* (5) Could not find the path */
  FR_INVALID_NAME,        /* (6) The path name format is invalid */
  FR_DENIED,              /* (7) Access denied due to prohibited access or directory full */
  FR_EXIST,               /* (8) Access denied due to prohibited access */
  FR_INVALID_OBJECT,      /* (9) The file/directory object is invalid */
  FR_WRITE_PROTECTED,     /* (10) The physical drive is write protected */
  FR_INVALID_DRIVE,       /* (11) The logical drive number is invalid */
  FR_NOT_ENABLED,         /* (12) The volume has no work area */
  FR_NO_FILESYSTEM,       /* (13) There is no valid FAT volume */
  FR_MKFS_ABORTED,        /* (14) The f_mkfs() aborted due to any problem */
  FR_TIMEOUT,             /* (15) Could not get a grant to access the volume within defined period */
  FR_LOCKED,              /* (16) The operation is rejected according to the file sharing policy */
  FR_NOT_ENOUGH_CORE,     /* (17) LFN working buffer could not be allocated */
  FR_TOO_MANY_OPEN_FILES, /* (18) Number of open files > FF_FS_LOCK */
  FR_INVALID_PARAMETER    /* (19) Given parameter is invalid */
} fs_error;

typedef uint8_t FRESULT;
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
  FileInterface(SdfsHost *, std::string, const char);
#else
  FileInterface(std::string, const char);
#endif
  ~FileInterface();

  bool close();
  bool seek(size_t pos);
  bool flush();
  size_t read(void *buf, size_t);
  size_t write(void *buf, size_t);
  char get();
  bool put(char);
  // void putback();
  fptr *get_fptr();
  std::string get_path();
  std::string get_name();
  size_t get_size();

 private:
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
  FileInterface *open_file(std::string path, const char mode);

 protected:
  FileInfo info;
  // std::string build_path(std::string);
  bool is_ready();
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