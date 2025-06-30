#pragma once
#include "esphome/core/defines.h"
#if defined(USE_ESP_IDF) && defined(USE_WEBSERVER_OTA)

#include <string>
#include <cctype>
#include <cstring>

namespace esphome {
namespace web_server_idf {

// Case-insensitive string prefix check
bool str_startswith_case_insensitive(const std::string &str, const std::string &prefix);

// Find a substring case-insensitively
size_t str_find_case_insensitive(const std::string &haystack, const std::string &needle, size_t pos = 0);

// Extract a parameter value from a header line
// Handles both quoted and unquoted values
std::string extract_header_param(const std::string &header, const std::string &param);

// Parse boundary from Content-Type header
// Returns true if boundary found, false otherwise
// boundary_start and boundary_len will point to the boundary value
bool parse_multipart_boundary(const char *content_type, const char **boundary_start, size_t *boundary_len);

// Trim whitespace from both ends of a string
std::string str_trim(const std::string &str);

}  // namespace web_server_idf
}  // namespace esphome
#endif  // defined(USE_ESP_IDF) && defined(USE_WEBSERVER_OTA)
