#pragma once
#include "sdfs.h"

#if !defined(USE_ESP8266)
#include "ff.h"
#else
typedef uint8_t FRESULT;
#endif

namespace esphome {
namespace sdfs {
typedef FRESULT fs_err_t;

//  FatFs Description
// https://elm-chan.org/fsw/ff/00index_e.html

class FileInterface {
  fs_err_t get_error();
  bool close();
  bool seek();
  bool flush();
  size_t read(const char *, size_t);
  size_t write(const char *, size_t);
  char *get();
  void put(char *);
  void putback();
};

class FsInterface {
  fs_err_t get_error();
  bool is_exist(std::string);
  bool is_dir(std::string);
  bool rmdir(std::string);
  bool rmfile(std::string);
  bool mkdir(std::string);
  bool rendir(std::string);
  bool renfile(std::string);
  size_t fsize(std::string);
  FsInterface get_dir(const char *);
  FileInterface open_file(std::string, const char *);
};

}  // namespace sdfs
}  // namespace esphome