#ifdef USE_ESP_IDF
#ifdef USE_WEBSERVER_OTA

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "multipart_parser.h"

namespace esphome {
namespace web_server_idf {
namespace test {

void print_test_result(const std::string &test_name, bool passed) {
  std::cout << test_name << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

bool test_simple_multipart() {
  std::string boundary = "----WebKitFormBoundary1234567890";
  std::string data = "------WebKitFormBoundary1234567890\r\n"
                     "Content-Disposition: form-data; name=\"file\"; filename=\"test.bin\"\r\n"
                     "Content-Type: application/octet-stream\r\n"
                     "\r\n"
                     "Hello World!\r\n"
                     "------WebKitFormBoundary1234567890--\r\n";

  MultipartParser parser(boundary);
  bool result = parser.parse(reinterpret_cast<const uint8_t *>(data.c_str()), data.length());

  if (!result) {
    return false;
  }

  MultipartParser::Part part;
  if (!parser.get_current_part(part)) {
    return false;
  }

  return part.filename == "test.bin" && part.name == "file" && part.length == 12 &&
         memcmp(part.data, "Hello World!", 12) == 0;
}

bool test_chunked_parsing() {
  std::string boundary = "----WebKitFormBoundary1234567890";
  std::string data = "------WebKitFormBoundary1234567890\r\n"
                     "Content-Disposition: form-data; name=\"firmware\"; filename=\"app.bin\"\r\n"
                     "Content-Type: application/octet-stream\r\n"
                     "\r\n"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ\r\n"
                     "------WebKitFormBoundary1234567890--\r\n";

  MultipartParser parser(boundary);

  // Parse in small chunks
  size_t chunk_size = 10;
  bool found_part = false;

  for (size_t i = 0; i < data.length(); i += chunk_size) {
    size_t len = std::min(chunk_size, data.length() - i);
    bool has_part = parser.parse(reinterpret_cast<const uint8_t *>(data.c_str() + i), len);

    if (has_part && !found_part) {
      found_part = true;
      MultipartParser::Part part;
      if (!parser.get_current_part(part)) {
        return false;
      }

      return part.filename == "app.bin" && part.name == "firmware" && part.length == 26 &&
             memcmp(part.data, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26) == 0;
    }
  }

  return found_part;
}

bool test_multiple_parts() {
  std::string boundary = "----WebKitFormBoundary1234567890";
  std::string data = "------WebKitFormBoundary1234567890\r\n"
                     "Content-Disposition: form-data; name=\"field1\"\r\n"
                     "\r\n"
                     "value1\r\n"
                     "------WebKitFormBoundary1234567890\r\n"
                     "Content-Disposition: form-data; name=\"file\"; filename=\"test.bin\"\r\n"
                     "Content-Type: application/octet-stream\r\n"
                     "\r\n"
                     "Binary content here\r\n"
                     "------WebKitFormBoundary1234567890--\r\n";

  MultipartParser parser(boundary);
  std::vector<MultipartParser::Part> parts;

  // Parse all at once
  size_t offset = 0;
  while (offset < data.length()) {
    size_t chunk_size = data.length() - offset;
    bool has_part = parser.parse(reinterpret_cast<const uint8_t *>(data.c_str() + offset), chunk_size);

    if (has_part) {
      MultipartParser::Part part;
      if (parser.get_current_part(part)) {
        parts.push_back(part);
        parser.consume_part();
      }
    }

    offset += chunk_size;

    if (parser.is_done()) {
      break;
    }
  }

  if (parts.size() != 2) {
    return false;
  }

  // Check first part (form field)
  if (parts[0].name != "field1" || !parts[0].filename.empty() || parts[0].length != 6 ||
      memcmp(parts[0].data, "value1", 6) != 0) {
    return false;
  }

  // Check second part (file)
  if (parts[1].name != "file" || parts[1].filename != "test.bin" || parts[1].length != 19 ||
      memcmp(parts[1].data, "Binary content here", 19) != 0) {
    return false;
  }

  return true;
}

bool test_boundary_edge_cases() {
  // Test when boundary is split across chunks
  std::string boundary = "----WebKitFormBoundary1234567890";
  std::string data = "------WebKitFormBoundary1234567890\r\n"
                     "Content-Disposition: form-data; name=\"file\"; filename=\"test.bin\"\r\n"
                     "\r\n"
                     "Content before boundary\r\n"
                     "------WebKitFormBoundary1234567890--\r\n";

  MultipartParser parser(boundary);

  // Parse with boundary split across chunks
  std::vector<std::string> chunks = {
      std::string(data.c_str(), 50),                        // Part of headers
      std::string(data.c_str() + 50, 60),                   // Rest of headers + start of content
      std::string(data.c_str() + 110, 20),                  // Middle of content
      std::string(data.c_str() + 130, data.length() - 130)  // End with boundary
  };

  bool found_part = false;
  for (const auto &chunk : chunks) {
    bool has_part = parser.parse(reinterpret_cast<const uint8_t *>(chunk.c_str()), chunk.length());

    if (has_part && !found_part) {
      found_part = true;
      MultipartParser::Part part;
      if (!parser.get_current_part(part)) {
        return false;
      }

      return part.filename == "test.bin" && part.length == 23 && memcmp(part.data, "Content before boundary", 23) == 0;
    }
  }

  return found_part;
}

bool test_empty_filename() {
  std::string boundary = "xyz123";
  std::string data = "--xyz123\r\n"
                     "Content-Disposition: form-data; name=\"field\"\r\n"
                     "\r\n"
                     "Just a regular field\r\n"
                     "--xyz123--\r\n";

  MultipartParser parser(boundary);
  bool result = parser.parse(reinterpret_cast<const uint8_t *>(data.c_str()), data.length());

  if (!result) {
    return false;
  }

  MultipartParser::Part part;
  if (!parser.get_current_part(part)) {
    return false;
  }

  return part.name == "field" && part.filename.empty() && part.length == 20 &&
         memcmp(part.data, "Just a regular field", 20) == 0;
}

bool test_content_type_header() {
  std::string boundary = "boundary123";
  std::string data = "--boundary123\r\n"
                     "Content-Disposition: form-data; name=\"upload\"; filename=\"data.json\"\r\n"
                     "Content-Type: application/json\r\n"
                     "\r\n"
                     "{\"key\": \"value\"}\r\n"
                     "--boundary123--\r\n";

  MultipartParser parser(boundary);
  bool result = parser.parse(reinterpret_cast<const uint8_t *>(data.c_str()), data.length());

  if (!result) {
    return false;
  }

  MultipartParser::Part part;
  if (!parser.get_current_part(part)) {
    return false;
  }

  return part.name == "upload" && part.filename == "data.json" && part.content_type == "application/json" &&
         part.length == 16 && memcmp(part.data, "{\"key\": \"value\"}", 16) == 0;
}

bool test_large_content() {
  std::string boundary = "----WebKitFormBoundary1234567890";

  // Generate large content
  std::string large_content;
  for (int i = 0; i < 1000; i++) {
    large_content += "0123456789";
  }

  std::string data = "------WebKitFormBoundary1234567890\r\n"
                     "Content-Disposition: form-data; name=\"firmware\"; filename=\"large.bin\"\r\n"
                     "\r\n" +
                     large_content +
                     "\r\n"
                     "------WebKitFormBoundary1234567890--\r\n";

  MultipartParser parser(boundary);

  // Parse in realistic chunks
  size_t chunk_size = 256;
  bool found_complete = false;
  size_t total_content_parsed = 0;

  for (size_t i = 0; i < data.length(); i += chunk_size) {
    size_t len = std::min(chunk_size, data.length() - i);
    bool has_part = parser.parse(reinterpret_cast<const uint8_t *>(data.c_str() + i), len);

    if (has_part) {
      MultipartParser::Part part;
      if (parser.get_current_part(part)) {
        // For large content, we might get it in pieces
        if (part.length == large_content.length()) {
          found_complete = true;
          return part.filename == "large.bin" && part.length == 10000 &&
                 memcmp(part.data, large_content.c_str(), part.length) == 0;
        }
      }
    }
  }

  return found_complete;
}

bool test_reset_parser() {
  std::string boundary = "test";
  std::string data1 = "--test\r\n"
                      "Content-Disposition: form-data; name=\"file1\"; filename=\"a.txt\"\r\n"
                      "\r\n"
                      "AAA\r\n"
                      "--test--\r\n";

  std::string data2 = "--test\r\n"
                      "Content-Disposition: form-data; name=\"file2\"; filename=\"b.txt\"\r\n"
                      "\r\n"
                      "BBB\r\n"
                      "--test--\r\n";

  MultipartParser parser(boundary);

  // Parse first data
  parser.parse(reinterpret_cast<const uint8_t *>(data1.c_str()), data1.length());
  MultipartParser::Part part1;
  parser.get_current_part(part1);

  // Reset and parse second data
  parser.reset();
  parser.parse(reinterpret_cast<const uint8_t *>(data2.c_str()), data2.length());
  MultipartParser::Part part2;
  parser.get_current_part(part2);

  return part1.filename == "a.txt" && part1.length == 3 && memcmp(part1.data, "AAA", 3) == 0 &&
         part2.filename == "b.txt" && part2.length == 3 && memcmp(part2.data, "BBB", 3) == 0;
}

void run_all_tests() {
  std::cout << "Running Multipart Parser Tests..." << std::endl;

  print_test_result("Simple multipart", test_simple_multipart());
  print_test_result("Chunked parsing", test_chunked_parsing());
  print_test_result("Multiple parts", test_multiple_parts());
  print_test_result("Boundary edge cases", test_boundary_edge_cases());
  print_test_result("Empty filename", test_empty_filename());
  print_test_result("Content-Type header", test_content_type_header());
  print_test_result("Large content", test_large_content());
  print_test_result("Reset parser", test_reset_parser());
}

}  // namespace test
}  // namespace web_server_idf
}  // namespace esphome

// Standalone test runner
int main() {
  esphome::web_server_idf::test::run_all_tests();
  return 0;
}

#endif  // USE_WEBSERVER_OTA
#endif  // USE_ESP_IDF