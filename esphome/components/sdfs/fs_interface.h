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
typedef uint8_t FRESULT;
typedef FsFile fptr;
#endif

namespace esphome {
namespace sdfs {

typedef struct {
  std::string name;
  std::string path;
  size_t size;
  bool is_dir = false;
  bool is_hidden = false;
  bool is_system = false;
  bool is_ro = false;
} FileInfo;

// typedef FRESULT fs_err_t;

//  FatFs Description
// https://elm-chan.org/fsw/ff/00index_e.html

class FileInterface {
 public:
  // fs_err_t get_error();
  FileInterface(std::string, const char);
  ~FileInterface();
  bool close();
  bool seek(size_t pos);
  bool flush();
  size_t read(void *buf, size_t);
  size_t write(void *buf, size_t);
  // char get();
  void put(char);
  // void putback();
  fptr *get_fptr();
  std::string get_path();
  std::string get_name();
  size_t get_size();

 private:
  uint8_t open_flag = 0;
  std::string path;
  fptr fp;
  FRESULT last_err = FR_OK;
  finfo info;
};

class FsInterface;
class FsIterator {
 public:
  FsIterator(std::string);
  ~FsIterator();
  FileInfo *get_next();

 private:
  dptr dp;
  FRESULT last_err = FR_OK;
  std::string path;
  FileInfo fi;
};

class FsInterface {
 public:
  // ~FsInterface();
  // FsInterface(std::string p);
  // fs_err_t error();
  void set_mountpoint(std::string p) { mount_point = p; }
  std::string build_path(std::string path);
  bool is_exist(std::string);
  bool is_dir(std::string);
  bool rename(std::string, std::string);
  bool mkdir(std::string);
  bool rmdir(std::string path);
  size_t size(std::string);
  FsIterator *list(std::string);
  FileInterface *open_file(std::string, const char);

 protected:
  std::string root_path = "/";
  std::string mount_point = "";
  // FF_DIR root_object;
  FRESULT last_err = FR_OK;
  bool exist = true;
};

}  // namespace sdfs
}  // namespace esphome