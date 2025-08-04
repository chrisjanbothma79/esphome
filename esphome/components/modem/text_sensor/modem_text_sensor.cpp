#ifdef USE_ESP_IDF

#include "esphome/core/defines.h"

#ifdef USE_MODEM
#ifdef USE_TEXT_SENSOR

#include "modem_text_sensor.h"

#include "esphome/core/log.h"
#include "esphome/core/application.h"

#include "../modem_component.h"
#include "../helpers.h"

#define ESPHL_ERROR_CHECK(err, message) \
  if ((err) != ESP_OK) { \
    ESP_LOGE(TAG, message ": (%d) %s", err, esp_err_to_name(err)); \
    this->mark_failed(); \
    return; \
  }

#define ESPMODEM_ERROR_CHECK(err, message) \
  if ((err) != command_result::OK) { \
    ESP_LOGE(TAG, message ": %s", command_result_to_string(err).c_str()); \
  }

namespace esphome {
namespace modem {

using namespace esp_modem;

static const char *const TAG = "modem.text_sensor";

void ModemTextSensor::setup() { ESP_LOGI(TAG, "Setting up Modem Sensor..."); }

void ModemTextSensor::update() {
  ESP_LOGD(TAG, "Modem text_sensor update");
  if (modem::global_modem_component->modem_handler->dce &&
      modem::global_modem_component->modem_handler->dce->sync() == command_result::OK) {
    this->update_network_type_text_sensor_();
    this->update_signal_strength_text_sensor_();
    this->update_nmea_text_sensor_();
  }
}

void ModemTextSensor::update_network_type_text_sensor_() {
  if (modem::global_modem_component->modem_handler->dce &&
      modem::global_modem_component->modem_handler->dce->sync() == command_result::OK &&
      this->network_type_text_sensor_) {
    int act;
    std::string network_type = "Not available";
    if (modem::global_modem_component->modem_handler->dce->get_network_system_mode(act) == command_result::OK) {
      network_type = network_system_mode_to_string(act);
    }
    this->network_type_text_sensor_->publish_state(network_type);
  }
}

void ModemTextSensor::update_signal_strength_text_sensor_() {
  if (modem::global_modem_component->modem_handler->dce &&
      modem::global_modem_component->modem_handler->dce->sync() == command_result::OK &&
      this->signal_strength_text_sensor_) {
    float rssi, ber;
    if (modem::global_modem_component->modem_handler->get_signal_quality(rssi, ber)) {
      std::string bars = get_signal_bars(rssi, false);
      this->signal_strength_text_sensor_->publish_state(bars);
    }
  }
}

void ModemTextSensor::update_nmea_text_sensor_() {
  if (modem::global_modem_component->modem_handler->dce &&
      modem::global_modem_component->modem_handler->dce->sync() == command_result::OK && this->nmea_text_sensor_) {
    std::string gnss_command_result = modem::global_modem_component->modem_handler->send_at(this->gnss_command_).output;
    ESP_LOGI(TAG, "GNSS command result: '%s'", gnss_command_result.c_str());
    auto parts = get_gnssinfo_tokens(gnss_command_result);

    if (parts.size() <= 1) {
      ESP_LOGW(TAG, "No valid GNSS data received");
      return;
    } else {
      ESP_LOGI(TAG, "size: %d", parts.size());
      for (const auto &part : parts) {
        ESP_LOGI(TAG, "%s: %s", part.first.c_str(), part.second.c_str());
      }
      yield;
      delay(1000);
    }

    float lat = NAN;
    float lon = NAN;

    if (parts["lon_lat_format"] == "DDMM.MM") {
      float lat_deg = parts["latitude"].empty() ? NAN : std::stof(parts["latitude"].substr(0, 2));
      float lat_min = parts["latitude"].empty() ? NAN : std::stof(parts["latitude"].substr(2));
      lat = lat_deg + (lat_min / 60.0);
      if (parts["lat_dir"] == "S")
        lat = -lat;

      float lon_deg = parts["longitude"].empty() ? NAN : std::stof(parts["longitude"].substr(0, 3));
      float lon_min = parts["longitude"].empty() ? NAN : std::stof(parts["longitude"].substr(3));
      lon = lon_deg + (lon_min / 60.0);
      if (parts["lon_dir"] == "W")
        lon = -lon;
    } else if (parts["lon_lat_format"] == "DD.DD") {
      lat = parts["latitude"].empty() ? NAN : std::stof(parts["latitude"]);
      if (parts["lat_dir"] == "S")
        lat = -lat;

      lon = parts["longitude"].empty() ? NAN : std::stof(parts["longitude"]);
      if (parts["lon_dir"] == "W")
        lon = -lon;
    }

    float alt = parts["altitude"].empty() ? NAN : std::stof(parts["altitude"]);
    float speed_knots = parts["speed"].empty() ? NAN : std::stof(parts["speed"]);
    float speed_kmh = speed_knots * 1.852;  // Convert speed from knots to km/h
    float cog = parts["cog"].empty() ? NAN : std::stof(parts["cog"]);
    float pdop = parts["pdop"].empty() ? NAN : std::stof(parts["pdop"]);
    float hdop = parts["hdop"].empty() ? NAN : std::stof(parts["hdop"]);
    float vdop = parts["vdop"].empty() ? NAN : std::stof(parts["vdop"]);
    int mode = parts["mode"].empty() ? 0 : std::stoi(parts["mode"]);
    int gps_svs = parts["sat_used_count"].empty() ? 0 : std::stoi(parts["sat_used_count"]);
    int glonass_svs = parts["sat_view_count"].empty() ? NAN : std::stoi(parts["sat_view_count"]);
    int beidou_svs = parts["sat_view_count_2"].empty() ? 0 : std::stoi(parts["sat_view_count_2"]);

    int day = parts["date"].empty() ? 0 : std::stoi(parts["date"].substr(0, 2));
    int month = parts["date"].empty() ? 0 : std::stoi(parts["date"].substr(2, 2));
    int year = parts["date"].empty() ? 0 : std::stoi(parts["date"].substr(4, 2)) + 2000;

    int hour = parts["time"].empty() ? 0 : std::stoi(parts["time"].substr(0, 2));
    int minute = parts["time"].empty() ? 0 : std::stoi(parts["time"].substr(2, 2));
    int second = parts["time"].empty() ? 0 : std::stoi(parts["time"].substr(4, 2));

    ESP_LOGV(TAG, "Latitude: %f, Longitude: %f", lat, lon);
    ESP_LOGV(TAG, "Altitude: %f m", alt);
    ESP_LOGV(TAG, "Speed: %f km/h", speed_kmh);
    ESP_LOGV(TAG, "COG: %f degrees", cog);
    ESP_LOGV(TAG, "PDOP: %f", pdop);
    ESP_LOGV(TAG, "HDOP: %f", hdop);
    ESP_LOGV(TAG, "VDOP: %f", vdop);
    ESP_LOGV(TAG, "GPS SVs: %d", gps_svs);
    ESP_LOGV(TAG, "GLONASS SVs: %d", glonass_svs);
    ESP_LOGV(TAG, "BEIDOU SVs: %d", beidou_svs);
    ESP_LOGV(TAG, "Fix mode: %d", mode);
    ESP_LOGV(TAG, "Date: %04d-%02d-%02d", year, month, day);
    ESP_LOGV(TAG, "Time: %02d:%02d:%02d", hour, minute, second);

    if (std::isnan(lat) || std::isnan(lon) || gps_svs <= 0 || std::isnan(hdop)) {
      ESP_LOGW(TAG, "GNSS data not available");
      return;
    }

    // NMEA sentence generation
    char lat_str[16] = "";
    char lon_str[16] = "";
    char time_str[10] = "";
    char date_str[7] = "";
    char alt_str[12] = "0.0";

    char lat_dir = (lat < 0) ? 'S' : 'N';
    char lon_dir = (lon < 0) ? 'W' : 'E';

    float abs_lat = fabs(lat);
    int lat_deg = (int) abs_lat;
    float lat_min = (abs_lat - lat_deg) * 60.0;
    snprintf(lat_str, sizeof(lat_str), "%02d%07.4f", lat_deg, lat_min);

    float abs_lon = fabs(lon);
    int lon_deg = (int) abs_lon;
    float lon_min = (abs_lon - lon_deg) * 60.0;
    snprintf(lon_str, sizeof(lon_str), "%03d%07.4f", lon_deg, lon_min);

    snprintf(time_str, sizeof(time_str), "%02d%02d%02d.00", hour, minute, second);
    snprintf(date_str, sizeof(date_str), "%02d%02d%02d", day, month, year % 100);

    if (!std::isnan(alt)) {
      snprintf(alt_str, sizeof(alt_str), "%.1f", alt);
    }

    // --- GPGGA ---
    char gga[128];
    snprintf(gga, sizeof(gga), "GPGGA,%s,%s,%c,%s,%c,1,%02d,%.2f,%s,M,,M,,", time_str, lat_str, lat_dir, lon_str,
             lon_dir, gps_svs, std::isnan(hdop) ? 99.9f : hdop, alt_str);
    uint8_t cs_gga = 0;
    for (int i = 0; gga[i] != '\0'; i++)
      cs_gga ^= gga[i];
    char full_gga[136];
    snprintf(full_gga, sizeof(full_gga), "$%s*%02X", gga, cs_gga);

    // --- GPRMC ---
    if (std::isnan(speed_knots))
      speed_knots = 0;
    if (std::isnan(cog))
      cog = 0;

    char rmc[128];
    snprintf(rmc, sizeof(rmc), "GPRMC,%s,A,%s,%c,%s,%c,%.2f,%.2f,%s,,,", time_str, lat_str, lat_dir, lon_str, lon_dir,
             speed_knots, cog, date_str);
    uint8_t cs_rmc = 0;
    for (int i = 0; rmc[i] != '\0'; i++)
      cs_rmc ^= rmc[i];
    char full_rmc[136];
    snprintf(full_rmc, sizeof(full_rmc), "$%s*%02X", rmc, cs_rmc);

    ESP_LOGI(TAG, "GPGGA: %s", full_gga);
    ESP_LOGI(TAG, "GPRMC: %s", full_rmc);

    this->nmea_text_sensor_->publish_state(full_gga);
    this->nmea_text_sensor_->publish_state(full_rmc);
  }
}

std::map<std::string, std::string> get_gnssinfo_tokens(const std::string &line) {
  std::map<std::string, std::string> out;
#ifdef USE_MODEM_GNSS_PARSER_CGNSSINFO16
  const char *input = line.c_str();
  const char *start = strchr(input, ':');
  if (!start)
    return out;

  start += 2;  // skip colon and space
  char buffer[256];
  strncpy(buffer, start, sizeof(buffer));
  buffer[sizeof(buffer) - 1] = '\0';

  const char *keys[16] = {"mode",      "sat_used_count", "sat_view_count", "fix_status", "latitude", "lat_dir",
                          "longitude", "lon_dir",        "date",           "time",       "altitude", "speed",
                          "cog",       "hdop",           "vdop",           "pdop"};

  char *token;
  char *saveptr;
  int i = 0;

  token = strtok_r(buffer, ",", &saveptr);
  while (token && i < 16) {
    out[keys[i]] = token ? token : "";
    token = strtok_r(nullptr, ",", &saveptr);
    i++;
  }

  out["lon_lat_format"] = "DDMM.MM";
#endif  // USE_MODEM_GNSS_PARSER_CGNSSINFO16

#ifdef USE_MODEM_GNSS_PARSER_CGNSSINFO18
  const char *input = line.c_str();
  const char *start = strchr(input, ':');
  if (!start)
    return out;

  start += 2;
  char buffer[384];
  strncpy(buffer, start, sizeof(buffer));
  buffer[sizeof(buffer) - 1] = '\0';

  const char *keys[18] = {
      "mode",             //  0
      "sat_used_count",   //  1
      "fix_status",       //  2
      "sat_view_count",   //  3
      "fix_status_2",     //  4
      "latitude",         //  5
      "lat_dir",          //  6
      "longitude",        //  7
      "lon_dir",          //  8
      "date",             //  9
      "time",             // 10
      "altitude",         // 11
      "speed",            // 12
      "cog",              // 13
      "hdop",             // 14
      "vdop",             // 15
      "pdop",             // 16
      "sat_view_count_2"  // 17
  };

  char *token;
  char *saveptr;
  int i = 0;

  token = strtok_r(buffer, ",", &saveptr);
  while (token && i < 18) {
    out[keys[i]] = token ? token : "";
    token = strtok_r(nullptr, ",", &saveptr);
    i++;
  }

  if (i != 18) {
    ESP_LOGW(TAG, "Expected 18 tokens in CGNSSINFO, got %d", i);
    return {};
  }

  out["lon_lat_format"] = "DD.DD";

#endif  // USE_MODEM_GNSS_PARSER_CGNSSINFO18
  return out;
}

}  // namespace modem
}  // namespace esphome

#endif  // USE_MODEM
#endif  // USE_TEXT_SENSOR
#endif  // USE_ESP_IDF
