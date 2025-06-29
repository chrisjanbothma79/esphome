#include "web_server_base.h"
#ifdef USE_NETWORK
#include "esphome/core/application.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

#ifdef USE_ARDUINO
#include <StreamString.h>
#if defined(USE_ESP32) || defined(USE_LIBRETINY)
#include <Update.h>
#endif
#ifdef USE_ESP8266
#include <Updater.h>
#endif
#endif

#if defined(USE_ESP_IDF) && defined(USE_WEBSERVER_OTA)
#include "esphome/components/ota/ota_backend.h"
#endif

namespace esphome {
namespace web_server_base {

static const char *const TAG = "web_server_base";

void WebServerBase::add_handler(AsyncWebHandler *handler) {
  // remove all handlers

  if (!credentials_.username.empty()) {
    handler = new internal::AuthMiddlewareHandler(handler, &credentials_);
  }
  this->handlers_.push_back(handler);
  if (this->server_ != nullptr) {
    this->server_->addHandler(handler);
  }
}

void report_ota_error() {
#ifdef USE_ARDUINO
  StreamString ss;
  Update.printError(ss);
  ESP_LOGW(TAG, "OTA Update failed! Error: %s", ss.c_str());
#endif
}

void OTARequestHandler::handleUpload(AsyncWebServerRequest *request, const String &filename, size_t index,
                                     uint8_t *data, size_t len, bool final) {
#ifdef USE_ARDUINO
  bool success;
  if (index == 0) {
    ESP_LOGI(TAG, "OTA Update Start: %s", filename.c_str());
    this->ota_read_length_ = 0;
#ifdef USE_ESP8266
    Update.runAsync(true);
    // NOLINTNEXTLINE(readability-static-accessed-through-instance)
    success = Update.begin((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000);
#endif
#if defined(USE_ESP32_FRAMEWORK_ARDUINO) || defined(USE_LIBRETINY)
    if (Update.isRunning()) {
      Update.abort();
    }
    success = Update.begin(UPDATE_SIZE_UNKNOWN, U_FLASH);
#endif
    if (!success) {
      report_ota_error();
      return;
    }
  } else if (Update.hasError()) {
    // don't spam logs with errors if something failed at start
    return;
  }

  success = Update.write(data, len) == len;
  if (!success) {
    report_ota_error();
    return;
  }
  this->ota_read_length_ += len;

  const uint32_t now = millis();
  if (now - this->last_ota_progress_ > 1000) {
    if (request->contentLength() != 0) {
      float percentage = (this->ota_read_length_ * 100.0f) / request->contentLength();
      ESP_LOGD(TAG, "OTA in progress: %0.1f%%", percentage);
    } else {
      ESP_LOGD(TAG, "OTA in progress: %u bytes read", this->ota_read_length_);
    }
    this->last_ota_progress_ = now;
  }

  if (final) {
    if (Update.end(true)) {
      ESP_LOGI(TAG, "OTA update successful!");
      this->parent_->set_timeout(100, []() { App.safe_reboot(); });
    } else {
      report_ota_error();
    }
  }
#endif

#if defined(USE_ESP_IDF) && defined(USE_WEBSERVER_OTA)
  // ESP-IDF implementation
  if (index == 0) {
    ESP_LOGI(TAG, "OTA Update Start: %s", filename.c_str());
    this->ota_read_length_ = 0;
    this->ota_started_ = false;

    // Create OTA backend
    this->ota_backend_ = ota::make_ota_backend();

    // Begin OTA with unknown size
    auto result = this->ota_backend_->begin(0);
    if (result != ota::OTA_RESPONSE_OK) {
      ESP_LOGE(TAG, "OTA begin failed: %d", result);
      this->ota_backend_.reset();
      return;
    }
    this->ota_started_ = true;
  } else if (!this->ota_started_ || !this->ota_backend_) {
    // Begin failed or was aborted
    return;
  }

  // Write data
  if (len > 0) {
    auto result = this->ota_backend_->write(data, len);
    if (result != ota::OTA_RESPONSE_OK) {
      ESP_LOGE(TAG, "OTA write failed: %d", result);
      this->ota_backend_->abort();
      this->ota_backend_.reset();
      this->ota_started_ = false;
      return;
    }

    this->ota_read_length_ += len;

    const uint32_t now = millis();
    if (now - this->last_ota_progress_ > 1000) {
      if (request->contentLength() != 0) {
        float percentage = (this->ota_read_length_ * 100.0f) / request->contentLength();
        ESP_LOGD(TAG, "OTA in progress: %0.1f%%", percentage);
      } else {
        ESP_LOGD(TAG, "OTA in progress: %u bytes read", this->ota_read_length_);
      }
      this->last_ota_progress_ = now;
    }
  }

  if (final) {
    auto result = this->ota_backend_->end();
    if (result == ota::OTA_RESPONSE_OK) {
      ESP_LOGI(TAG, "OTA update successful!");
      this->parent_->set_timeout(100, []() { App.safe_reboot(); });
    } else {
      ESP_LOGE(TAG, "OTA end failed: %d", result);
    }
    this->ota_backend_.reset();
    this->ota_started_ = false;
  }
#endif
}
void OTARequestHandler::handleRequest(AsyncWebServerRequest *request) {
#ifdef USE_ARDUINO
  AsyncWebServerResponse *response;
  if (!Update.hasError()) {
    response = request->beginResponse(200, "text/plain", "Update Successful!");
  } else {
    StreamString ss;
    ss.print("Update Failed: ");
    Update.printError(ss);
    response = request->beginResponse(200, "text/plain", ss);
  }
  response->addHeader("Connection", "close");
  request->send(response);
#endif
#if defined(USE_ESP_IDF) && defined(USE_WEBSERVER_OTA)
  AsyncWebServerResponse *response = request->beginResponse(
      200, "text/plain", (this->ota_started_ && this->ota_backend_) ? "Update Successful!" : "Update Failed!");
  response->addHeader("Connection", "close");
  request->send(response);
#endif
}

void WebServerBase::add_ota_handler() {
#if defined(USE_ARDUINO) || (defined(USE_ESP_IDF) && defined(USE_WEBSERVER_OTA))
  this->add_handler(new OTARequestHandler(this));  // NOLINT
#endif
}
float WebServerBase::get_setup_priority() const {
  // Before WiFi (captive portal)
  return setup_priority::WIFI + 2.0f;
}

}  // namespace web_server_base
}  // namespace esphome
#endif
