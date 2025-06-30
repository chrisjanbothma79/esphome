#pragma once
#include "esphome/core/defines.h"
#ifdef USE_ESP_IDF

#include <string>

namespace esphome {
namespace web_server_idf {

// Helper function for case-insensitive character comparison
inline bool char_equals_ci(char a, char b) { return ::tolower(a) == ::tolower(b); }

// Helper function for case-insensitive string region comparison
bool str_ncmp_ci(const char *s1, const char *s2, size_t n);

// Case-insensitive string search (like strstr but case-insensitive)
const char *stristr(const char *haystack, const char *needle);

}  // namespace web_server_idf
}  // namespace esphome
#endif  // USE_ESP_IDF
