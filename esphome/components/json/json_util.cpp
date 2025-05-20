#include "json_util.h"
#include "esphome/core/log.h"

namespace esphome {
namespace json {

static const char *const TAG = "json";

static auto ALLOCATOR = RAMAllocator<uint8_t>(
    RAMAllocator<uint8_t>::NONE);  // Attempt to allocate in PSRAM before falling back into internal

// Build an allocator for the JSON Library using the RAMAllocator class
struct SpiRamAllocator : ArduinoJson::Allocator {
  void *allocate(size_t size) { return ALLOCATOR.allocate(size); }

  void deallocate(void *pointer) {
    free(pointer);  // NOLINT(cppcoreguidelines-owning-memory,cppcoreguidelines-no-malloc)
  }

  void *reallocate(void *ptr, size_t new_size) { return ALLOCATOR.reallocate(static_cast<uint8_t *>(ptr), new_size); }
};

static auto DOC_ALLOCATOR = SpiRamAllocator();

std::string build_json(const json_build_t &f) {
  // Here we are allocating up to 5kb of memory,
  // with the heap size minus 2kb to be safe if less than 5kb
  // as we can not have a true dynamic sized document.
  // The excess memory is freed below with `shrinkToFit()`
  while (true) {
    ESP_LOGV(TAG, "Attempting to allocate %zu bytes for JSON serialization", request_size);
    DynamicJsonDocument json_document(request_size);
    if (json_document.capacity() == 0) {
      ESP_LOGE(TAG, "Could not allocate memory for JSON document!");
      return "{}";
    }
    JsonObject root = json_document.to<JsonObject>();
    f(root);
    if (json_document.overflowed()) {
      if (request_size == free_heap) {
        ESP_LOGE(TAG, "Could not allocate memory for JSON document!");
        return "{}";
      }
      request_size = std::min(request_size * 2, free_heap);
      continue;
    }
    std::string output;
    serializeJson(json_document, output);
    return output;
  }
}

bool parse_json(const std::string &data, const json_parse_t &f) {
  // Here we are allocating 1.5 times the data size,
  // with the heap size minus 2kb to be safe if less than that
  // as we can not have a true dynamic sized document.
  // The excess memory is freed below with `shrinkToFit()`
  while (true) {
    DynamicJsonDocument json_document(request_size);
    if (json_document.capacity() == 0) {
      ESP_LOGE(TAG, "Could not allocate memory for JSON document!");
      return false;
    }
    DeserializationError err = deserializeJson(json_document, data);

    JsonObject root = json_document.as<JsonObject>();

    if (err == DeserializationError::Ok) {
      return f(root);
    } else if (err == DeserializationError::NoMemory) {
      ESP_LOGE(TAG, "Can not allocate more memory for deserialization. Consider making source string smaller");
      return false;
    } else {
      ESP_LOGE(TAG, "Parse error: %s", err.c_str());
      return false;
    }
  };
  return false;
}

}  // namespace json
}  // namespace esphome
