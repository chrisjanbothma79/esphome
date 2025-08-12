#include "crc8_test_component.h"

namespace esphome {
namespace crc8_test_component {

static const char *const TAG = "crc8_test";

void CRC8TestComponent::setup() {
  ESP_LOGI(TAG, "CRC8 Helper Function Integration Test Starting");

  // Run all test suites
  test_crc8_dallas_maxim();
  test_crc8_sensirion_style();
  test_crc8_pec_style();
  test_crc8_parameter_equivalence();
  test_crc8_edge_cases();
  test_component_compatibility();

  ESP_LOGI(TAG, "CRC8 Integration Test Complete");
}

void CRC8TestComponent::test_crc8_dallas_maxim() {
  ESP_LOGI(TAG, "Testing Dallas/Maxim CRC8 (default parameters)");

  // Test vectors for Dallas/Maxim CRC8 (polynomial 0x8C, LSB-first, init 0x00)
  const uint8_t test1[] = {0x01};
  const uint8_t test2[] = {0xFF};
  const uint8_t test3[] = {0x12, 0x34};
  const uint8_t test4[] = {0xAA, 0xBB, 0xCC};
  const uint8_t test5[] = {0x01, 0x02, 0x03, 0x04, 0x05};

  bool all_passed = true;
  all_passed &= verify_crc8("Dallas [0x01]", test1, sizeof(test1), 0x5E);
  all_passed &= verify_crc8("Dallas [0xFF]", test2, sizeof(test2), 0x35);
  all_passed &= verify_crc8("Dallas [0x12, 0x34]", test3, sizeof(test3), 0xA2);
  all_passed &= verify_crc8("Dallas [0xAA, 0xBB, 0xCC]", test4, sizeof(test4), 0xD4);
  all_passed &= verify_crc8("Dallas [0x01...0x05]", test5, sizeof(test5), 0x2A);

  log_test_result("Dallas/Maxim CRC8", all_passed);
}

void CRC8TestComponent::test_crc8_sensirion_style() {
  ESP_LOGI(TAG, "Testing Sensirion CRC8 (0x31 poly, MSB-first, init 0xFF)");

  const uint8_t test1[] = {0x00};
  const uint8_t test2[] = {0x01};
  const uint8_t test3[] = {0xFF};
  const uint8_t test4[] = {0x12, 0x34};
  const uint8_t test5[] = {0xBE, 0xEF};

  bool all_passed = true;
  all_passed &= verify_crc8("Sensirion [0x00]", test1, sizeof(test1), 0xAC, 0xFF, 0x31, true);
  all_passed &= verify_crc8("Sensirion [0x01]", test2, sizeof(test2), 0x9D, 0xFF, 0x31, true);
  all_passed &= verify_crc8("Sensirion [0xFF]", test3, sizeof(test3), 0x00, 0xFF, 0x31, true);
  all_passed &= verify_crc8("Sensirion [0x12, 0x34]", test4, sizeof(test4), 0x37, 0xFF, 0x31, true);
  all_passed &= verify_crc8("Sensirion [0xBE, 0xEF]", test5, sizeof(test5), 0x92, 0xFF, 0x31, true);

  log_test_result("Sensirion CRC8", all_passed);
}

void CRC8TestComponent::test_crc8_pec_style() {
  ESP_LOGI(TAG, "Testing PEC CRC8 (0x07 poly, MSB-first, init 0x00)");

  const uint8_t test1[] = {0x00};
  const uint8_t test2[] = {0x01};
  const uint8_t test3[] = {0xFF};
  const uint8_t test4[] = {0x12, 0x34};
  const uint8_t test5[] = {0xAA, 0xBB};

  bool all_passed = true;
  all_passed &= verify_crc8("PEC [0x00]", test1, sizeof(test1), 0x00, 0x00, 0x07, true);
  all_passed &= verify_crc8("PEC [0x01]", test2, sizeof(test2), 0x07, 0x00, 0x07, true);
  all_passed &= verify_crc8("PEC [0xFF]", test3, sizeof(test3), 0xF3, 0x00, 0x07, true);
  all_passed &= verify_crc8("PEC [0x12, 0x34]", test4, sizeof(test4), 0xF1, 0x00, 0x07, true);
  all_passed &= verify_crc8("PEC [0xAA, 0xBB]", test5, sizeof(test5), 0xB2, 0x00, 0x07, true);

  log_test_result("PEC CRC8", all_passed);
}

void CRC8TestComponent::test_crc8_parameter_equivalence() {
  ESP_LOGI(TAG, "Testing parameter equivalence");

  const uint8_t test_data[] = {0x12, 0x34, 0x56, 0x78};

  // Test that default parameters work as expected
  uint8_t default_result = crc8(test_data, sizeof(test_data));
  uint8_t explicit_result = crc8(test_data, sizeof(test_data), 0x00, 0x8C, false);

  bool passed = (default_result == explicit_result);
  if (!passed) {
    ESP_LOGE(TAG, "Parameter equivalence FAILED: default=0x%02X, explicit=0x%02X", default_result, explicit_result);
  }

  log_test_result("Parameter equivalence", passed);
}

void CRC8TestComponent::test_crc8_edge_cases() {
  ESP_LOGI(TAG, "Testing edge cases");

  bool all_passed = true;

  // Test empty data (should return initial CRC)
  uint8_t empty_result = crc8(nullptr, 0, 0x42);
  if (empty_result != 0x42) {
    ESP_LOGE(TAG, "Empty data test FAILED: expected 0x42, got 0x%02X", empty_result);
    all_passed = false;
  } else {
    ESP_LOGI(TAG, "Empty data test PASSED");
  }

  // Test single byte with different init values
  const uint8_t single_byte[] = {0x42};
  uint8_t result1 = crc8(single_byte, 1, 0x00);
  uint8_t result2 = crc8(single_byte, 1, 0xFF);

  if (result1 == result2) {
    ESP_LOGE(TAG, "Different init values test FAILED: both produced 0x%02X", result1);
    all_passed = false;
  } else {
    ESP_LOGI(TAG, "Different init values test PASSED: 0x%02X vs 0x%02X", result1, result2);
  }

  // Test same data with different polynomials
  uint8_t result_8c = crc8(single_byte, 1, 0x00, 0x8C);
  uint8_t result_31 = crc8(single_byte, 1, 0x00, 0x31);
  uint8_t result_07 = crc8(single_byte, 1, 0x00, 0x07);

  if (result_8c == result_31 || result_8c == result_07 || result_31 == result_07) {
    ESP_LOGE(TAG, "Different polynomials test FAILED: 0x8C->%02X, 0x31->%02X, 0x07->%02X", result_8c, result_31,
             result_07);
    all_passed = false;
  } else {
    ESP_LOGI(TAG, "Different polynomials test PASSED: 0x8C->%02X, 0x31->%02X, 0x07->%02X", result_8c, result_31,
             result_07);
  }

  // Test MSB vs LSB processing
  uint8_t msb_result = crc8(single_byte, 1, 0x00, 0x8C, true);
  uint8_t lsb_result = crc8(single_byte, 1, 0x00, 0x8C, false);

  if (msb_result == lsb_result) {
    ESP_LOGE(TAG, "MSB vs LSB test FAILED: both produced 0x%02X", msb_result);
    all_passed = false;
  } else {
    ESP_LOGI(TAG, "MSB vs LSB test PASSED: MSB=0x%02X, LSB=0x%02X", msb_result, lsb_result);
  }

  log_test_result("Edge cases", all_passed);
}

void CRC8TestComponent::test_component_compatibility() {
  ESP_LOGI(TAG, "Testing component compatibility");

  bool all_passed = true;

  // AM2315C/HTE501/TEE501 compatibility test (Sensirion-style)
  const uint8_t am2315c_data[] = {0x68, 0x01};  // Temperature data
  all_passed &= verify_crc8("AM2315C compatibility", am2315c_data, sizeof(am2315c_data), 0xD2, 0xFF, 0x31, true);

  // MLX90614 PEC compatibility test
  const uint8_t mlx90614_data[] = {0xB4, 0x07};  // I2C write + register
  all_passed &= verify_crc8("MLX90614 PEC compatibility", mlx90614_data, sizeof(mlx90614_data), 0x0E, 0x00, 0x07, true);

  // LC709203F compatibility test (Dallas/Maxim style)
  const uint8_t lc709203f_data[] = {0x16, 0x01, 0x00};  // Example command
  all_passed &= verify_crc8("LC709203F compatibility", lc709203f_data, sizeof(lc709203f_data), 0x5F, 0x00, 0x8C, false);

  log_test_result("Component compatibility", all_passed);
}

void CRC8TestComponent::log_test_result(const char *test_name, bool passed) {
  if (passed) {
    ESP_LOGI(TAG, "TEST PASSED: %s", test_name);
  } else {
    ESP_LOGE(TAG, "TEST FAILED: %s", test_name);
  }
}

bool CRC8TestComponent::verify_crc8(const char *test_name, const uint8_t *data, uint8_t len, uint8_t expected,
                                    uint8_t crc, uint8_t poly, bool msb_first) {
  uint8_t result = crc8(data, len, crc, poly, msb_first);

  if (result == expected) {
    ESP_LOGI(TAG, "SUBTEST PASSED: %s -> 0x%02X", test_name, result);
    return true;
  } else {
    ESP_LOGE(TAG, "SUBTEST FAILED: %s -> expected 0x%02X, got 0x%02X (init=0x%02X, poly=0x%02X, msb=%s)", test_name,
             expected, result, crc, poly, msb_first ? "true" : "false");
    return false;
  }
}

}  // namespace crc8_test_component
}  // namespace esphome
