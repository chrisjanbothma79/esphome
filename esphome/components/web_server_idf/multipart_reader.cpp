#ifdef USE_ESP_IDF
#ifdef USE_WEBSERVER_OTA
#include "multipart_reader.h"
#include "esphome/core/log.h"
#include <cstring>
#include <cctype>

namespace esphome {
namespace web_server_idf {

static const char *const TAG = "multipart_reader";

MultipartReader::MultipartReader(const std::string &boundary) {
  // Initialize settings with callbacks
  memset(&settings_, 0, sizeof(settings_));
  settings_.on_header_field = on_header_field;
  settings_.on_header_value = on_header_value;
  settings_.on_part_data_begin = on_part_data_begin;
  settings_.on_part_data = on_part_data;
  settings_.on_part_data_end = on_part_data_end;
  settings_.on_headers_complete = on_headers_complete;

  // Create parser with boundary
  parser_ = multipart_parser_init(boundary.c_str(), &settings_);
  if (parser_) {
    multipart_parser_set_data(parser_, this);
  }
}

MultipartReader::~MultipartReader() {
  if (parser_) {
    multipart_parser_free(parser_);
  }
}

size_t MultipartReader::parse(const char *data, size_t len) {
  if (!parser_) {
    return 0;
  }
  return multipart_parser_execute(parser_, data, len);
}

int MultipartReader::on_header_field(multipart_parser *parser, const char *at, size_t length) {
  MultipartReader *reader = static_cast<MultipartReader *>(multipart_parser_get_data(parser));

  // If we were processing a value, save it
  if (!reader->current_header_value_.empty()) {
    // Process the previous header
    std::string field_lower = reader->current_header_field_;
    std::transform(field_lower.begin(), field_lower.end(), field_lower.begin(), ::tolower);

    if (field_lower == "content-disposition") {
      // Parse name and filename from Content-Disposition
      size_t name_pos = reader->current_header_value_.find("name=");
      if (name_pos != std::string::npos) {
        name_pos += 5;
        size_t end_pos;
        if (reader->current_header_value_[name_pos] == '"') {
          name_pos++;
          end_pos = reader->current_header_value_.find('"', name_pos);
        } else {
          end_pos = reader->current_header_value_.find_first_of("; \r\n", name_pos);
        }
        if (end_pos != std::string::npos) {
          reader->current_part_.name = reader->current_header_value_.substr(name_pos, end_pos - name_pos);
        }
      }

      size_t filename_pos = reader->current_header_value_.find("filename=");
      if (filename_pos != std::string::npos) {
        filename_pos += 9;
        size_t end_pos;
        if (reader->current_header_value_[filename_pos] == '"') {
          filename_pos++;
          end_pos = reader->current_header_value_.find('"', filename_pos);
        } else {
          end_pos = reader->current_header_value_.find_first_of("; \r\n", filename_pos);
        }
        if (end_pos != std::string::npos) {
          reader->current_part_.filename = reader->current_header_value_.substr(filename_pos, end_pos - filename_pos);
        }
      }
    } else if (field_lower == "content-type") {
      reader->current_part_.content_type = reader->current_header_value_;
    }

    reader->current_header_value_.clear();
  }

  // Start new header field
  reader->current_header_field_.assign(at, length);
  reader->in_headers_ = true;

  return 0;
}

int MultipartReader::on_header_value(multipart_parser *parser, const char *at, size_t length) {
  MultipartReader *reader = static_cast<MultipartReader *>(multipart_parser_get_data(parser));
  reader->current_header_value_.append(at, length);
  return 0;
}

int MultipartReader::on_headers_complete(multipart_parser *parser) {
  MultipartReader *reader = static_cast<MultipartReader *>(multipart_parser_get_data(parser));

  // Process last header if any
  if (!reader->current_header_value_.empty()) {
    std::string field_lower = reader->current_header_field_;
    std::transform(field_lower.begin(), field_lower.end(), field_lower.begin(), ::tolower);

    if (field_lower == "content-disposition") {
      // Parse name and filename from Content-Disposition
      size_t name_pos = reader->current_header_value_.find("name=");
      if (name_pos != std::string::npos) {
        name_pos += 5;
        size_t end_pos;
        if (reader->current_header_value_[name_pos] == '"') {
          name_pos++;
          end_pos = reader->current_header_value_.find('"', name_pos);
        } else {
          end_pos = reader->current_header_value_.find_first_of("; \r\n", name_pos);
        }
        if (end_pos != std::string::npos) {
          reader->current_part_.name = reader->current_header_value_.substr(name_pos, end_pos - name_pos);
        }
      }

      size_t filename_pos = reader->current_header_value_.find("filename=");
      if (filename_pos != std::string::npos) {
        filename_pos += 9;
        size_t end_pos;
        if (reader->current_header_value_[filename_pos] == '"') {
          filename_pos++;
          end_pos = reader->current_header_value_.find('"', filename_pos);
        } else {
          end_pos = reader->current_header_value_.find_first_of("; \r\n", filename_pos);
        }
        if (end_pos != std::string::npos) {
          reader->current_part_.filename = reader->current_header_value_.substr(filename_pos, end_pos - filename_pos);
        }
      }
    } else if (field_lower == "content-type") {
      reader->current_part_.content_type = reader->current_header_value_;
    }
  }

  reader->in_headers_ = false;
  reader->current_header_field_.clear();
  reader->current_header_value_.clear();

  ESP_LOGD(TAG, "Part headers complete: name='%s', filename='%s', content_type='%s'",
           reader->current_part_.name.c_str(), reader->current_part_.filename.c_str(),
           reader->current_part_.content_type.c_str());

  return 0;
}

int MultipartReader::on_part_data_begin(multipart_parser *parser) {
  MultipartReader *reader = static_cast<MultipartReader *>(multipart_parser_get_data(parser));
  ESP_LOGD(TAG, "Part data begin");
  return 0;
}

int MultipartReader::on_part_data(multipart_parser *parser, const char *at, size_t length) {
  MultipartReader *reader = static_cast<MultipartReader *>(multipart_parser_get_data(parser));

  // Only process file uploads
  if (reader->has_file() && reader->data_callback_) {
    reader->data_callback_(reinterpret_cast<const uint8_t *>(at), length);
  }

  return 0;
}

int MultipartReader::on_part_data_end(multipart_parser *parser) {
  MultipartReader *reader = static_cast<MultipartReader *>(multipart_parser_get_data(parser));

  ESP_LOGD(TAG, "Part data end");

  if (reader->part_complete_callback_) {
    reader->part_complete_callback_();
  }

  // Clear part info for next part
  reader->current_part_ = Part{};

  return 0;
}

}  // namespace web_server_idf
}  // namespace esphome
#endif  // USE_WEBSERVER_OTA
#endif  // USE_ESP_IDF