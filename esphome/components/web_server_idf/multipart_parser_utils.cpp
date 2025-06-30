#include "esphome/core/defines.h"
#if defined(USE_ESP_IDF) && defined(USE_WEBSERVER_OTA)
#include "multipart_parser_utils.h"
#include "parser_utils.h"
#include "esphome/core/log.h"

namespace esphome {
namespace web_server_idf {

// Case-insensitive string prefix check
bool str_startswith_case_insensitive(const std::string &str, const std::string &prefix) {
  if (str.length() < prefix.length()) {
    return false;
  }
  return str_ncmp_ci(str.c_str(), prefix.c_str(), prefix.length());
}

// Find a substring case-insensitively
size_t str_find_case_insensitive(const std::string &haystack, const std::string &needle, size_t pos) {
  if (needle.empty() || pos >= haystack.length()) {
    return std::string::npos;
  }

  const size_t needle_len = needle.length();
  const size_t max_pos = haystack.length() - needle_len;

  for (size_t i = pos; i <= max_pos; i++) {
    if (str_ncmp_ci(haystack.c_str() + i, needle.c_str(), needle_len)) {
      return i;
    }
  }

  return std::string::npos;
}

// Extract a parameter value from a header line
// Handles both quoted and unquoted values
std::string extract_header_param(const std::string &header, const std::string &param) {
  size_t search_pos = 0;

  while (search_pos < header.length()) {
    // Look for param name
    size_t pos = str_find_case_insensitive(header, param, search_pos);
    if (pos == std::string::npos) {
      return "";
    }

    // Check if this is a word boundary (not part of another parameter)
    if (pos > 0 && header[pos - 1] != ' ' && header[pos - 1] != ';' && header[pos - 1] != '\t') {
      search_pos = pos + 1;
      continue;
    }

    // Move past param name
    pos += param.length();

    // Skip whitespace and find '='
    while (pos < header.length() && (header[pos] == ' ' || header[pos] == '\t')) {
      pos++;
    }

    if (pos >= header.length() || header[pos] != '=') {
      search_pos = pos;
      continue;
    }

    pos++;  // Skip '='

    // Skip whitespace after '='
    while (pos < header.length() && (header[pos] == ' ' || header[pos] == '\t')) {
      pos++;
    }

    if (pos >= header.length()) {
      return "";
    }

    // Check if value is quoted
    if (header[pos] == '"') {
      pos++;
      size_t end = header.find('"', pos);
      if (end != std::string::npos) {
        return header.substr(pos, end - pos);
      }
      // Malformed - no closing quote
      return "";
    }

    // Unquoted value - find the end (semicolon, comma, or end of string)
    size_t end = pos;
    while (end < header.length() && header[end] != ';' && header[end] != ',' && header[end] != ' ' &&
           header[end] != '\t') {
      end++;
    }

    return header.substr(pos, end - pos);
  }

  return "";
}

// Parse boundary from Content-Type header
// Returns true if boundary found, false otherwise
// boundary_start and boundary_len will point to the boundary value
bool parse_multipart_boundary(const char *content_type, const char **boundary_start, size_t *boundary_len) {
  if (!content_type) {
    return false;
  }

  // Check for multipart/form-data (case-insensitive)
  if (!stristr(content_type, "multipart/form-data")) {
    return false;
  }

  // Look for boundary parameter
  const char *b = stristr(content_type, "boundary=");
  if (!b) {
    return false;
  }

  const char *start = b + 9;  // Skip "boundary="

  // Skip whitespace
  while (*start == ' ' || *start == '\t') {
    start++;
  }

  if (!*start) {
    return false;
  }

  // Find end of boundary
  const char *end = start;
  if (*end == '"') {
    // Quoted boundary
    start++;
    end++;
    while (*end && *end != '"') {
      end++;
    }
    *boundary_len = end - start;
  } else {
    // Unquoted boundary
    while (*end && *end != ' ' && *end != ';' && *end != '\r' && *end != '\n' && *end != '\t') {
      end++;
    }
    *boundary_len = end - start;
  }

  if (*boundary_len == 0) {
    return false;
  }

  *boundary_start = start;

  // Debug log the extracted boundary
  ESP_LOGV("multipart_utils", "Extracted boundary: '%.*s' (len: %zu)", (int) *boundary_len, start, *boundary_len);

  return true;
}

// Trim whitespace from both ends of a string
std::string str_trim(const std::string &str) {
  size_t start = str.find_first_not_of(" \t\r\n");
  if (start == std::string::npos) {
    return "";
  }
  size_t end = str.find_last_not_of(" \t\r\n");
  return str.substr(start, end - start + 1);
}

}  // namespace web_server_idf
}  // namespace esphome
#endif  // defined(USE_ESP_IDF) && defined(USE_WEBSERVER_OTA)
