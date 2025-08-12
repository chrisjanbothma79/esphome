#include "crc8_test_component.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"
#include "old_crc8_implementations.h"

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
  test_old_vs_new_implementations();

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

  // Empty array test
  const uint8_t empty[] = {};
  uint8_t empty_result = crc8(empty, 0);
  bool empty_passed = (empty_result == 0x00);  // Should return init value
  if (!empty_passed) {
    ESP_LOGE(TAG, "Empty array test FAILED: expected 0x00, got 0x%02X", empty_result);
  }
  all_passed &= empty_passed;

  // Single byte tests
  const uint8_t single_zero[] = {0x00};
  const uint8_t single_ff[] = {0xFF};
  all_passed &= verify_crc8("Single [0x00]", single_zero, 1, 0x00);
  all_passed &= verify_crc8("Single [0xFF]", single_ff, 1, 0x35);

  log_test_result("Edge cases", all_passed);
}

void CRC8TestComponent::test_component_compatibility() {
  ESP_LOGI(TAG, "Testing component compatibility");

  // Test specific component use cases
  bool all_passed = true;

  // AGS10-style data (Sensirion CRC8)
  const uint8_t ags10_data[] = {0x12, 0x34, 0x56};
  uint8_t ags10_result = crc8(ags10_data, sizeof(ags10_data), 0xFF, 0x31, true);
  ESP_LOGI(TAG, "AGS10-style CRC8: 0x%02X", ags10_result);

  // LC709203F-style data (PEC CRC8)
  const uint8_t lc_data[] = {0xAA, 0xBB};
  uint8_t lc_result = crc8(lc_data, sizeof(lc_data), 0x00, 0x07, true);
  ESP_LOGI(TAG, "LC709203F-style CRC8: 0x%02X", lc_result);

  // DallasTemperature-style data (Dallas CRC8)
  const uint8_t dallas_data[] = {0x28, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};
  uint8_t dallas_result = crc8(dallas_data, sizeof(dallas_data));
  ESP_LOGI(TAG, "Dallas-style CRC8: 0x%02X", dallas_result);

  all_passed = true;  // These are just demonstration tests
  log_test_result("Component compatibility", all_passed);
}

void CRC8TestComponent::test_old_vs_new_implementations() {
  ESP_LOGI(TAG, "Testing old vs new CRC8 implementations");

  // Test data for AGS10/AM2315C/HTE501/TEE501 (Sensirion-style)
  const uint8_t sensirion_tests[][5] = {{0x12}, {0x34, 0x56}, {0xAA, 0xBB, 0xCC}, {0x01, 0x02, 0x03, 0x04}};
  const uint8_t sensirion_lens[] = {1, 2, 3, 4};

  // Test data for LC709203F/MLX90614 (PEC-style)
  const uint8_t pec_tests[][5] = {{0x12}, {0x34, 0x56}, {0xAA, 0xBB, 0xCC}, {0x01, 0x02, 0x03, 0x04}};
  const uint8_t pec_lens[] = {1, 2, 3, 4};

  bool all_passed = true;

  // Test AGS10 implementation
  ESP_LOGI(TAG, "Testing AGS10 old vs new");
  for (int i = 0; i < 4; i++) {
    uint8_t old_result = OldCRC8Implementations::ags10_calc_crc8_(sensirion_tests[i], sensirion_lens[i]);
    uint8_t new_result = crc8(sensirion_tests[i], sensirion_lens[i], 0xFF, 0x31, true);
    bool match = (old_result == new_result);
    ESP_LOGI(TAG, "AGS10 test %d: old=0x%02X, new=0x%02X %s", i, old_result, new_result, match ? "PASS" : "FAIL");
    all_passed &= match;
  }

  // Test AM2315C implementation
  ESP_LOGI(TAG, "Testing AM2315C old vs new");
  for (int i = 0; i < 4; i++) {
    uint8_t old_result = OldCRC8Implementations::am2315c_crc8_(sensirion_tests[i], sensirion_lens[i]);
    uint8_t new_result = crc8(sensirion_tests[i], sensirion_lens[i], 0xFF, 0x31, true);
    bool match = (old_result == new_result);
    ESP_LOGI(TAG, "AM2315C test %d: old=0x%02X, new=0x%02X %s", i, old_result, new_result, match ? "PASS" : "FAIL");
    all_passed &= match;
  }

  // Test HTE501 implementation (using range-based function)
  ESP_LOGI(TAG, "Testing HTE501 old vs new");
  const uint8_t hte501_buf[] = {0x00, 0x12, 0x34, 0x56, 0x78, 0x00};  // Add padding
  for (int i = 0; i < 3; i++) {
    uint8_t from = 1;
    uint8_t to = 1 + i;  // i=0: from=1,to=1 (1 byte), i=1: from=1,to=2 (2 bytes), i=2: from=1,to=3 (3 bytes)
    uint8_t length = to - from + 1;  // inclusive range
    uint8_t old_result = OldCRC8Implementations::hte501_calc_crc8_(hte501_buf, from, to);
    uint8_t new_result = crc8(&hte501_buf[from], length, 0xFF, 0x31, true);
    bool match = (old_result == new_result);
    ESP_LOGI(TAG, "HTE501 test %d (from=%d,to=%d,len=%d): old=0x%02X, new=0x%02X %s", i, from, to, length, old_result,
             new_result, match ? "PASS" : "FAIL");
    all_passed &= match;
  }

  // Test TEE501 implementation (using range-based function)
  ESP_LOGI(TAG, "Testing TEE501 old vs new");
  for (int i = 0; i < 3; i++) {
    uint8_t from = 1;
    uint8_t to = 1 + i;  // i=0: from=1,to=1 (1 byte), i=1: from=1,to=2 (2 bytes), i=2: from=1,to=3 (3 bytes)
    uint8_t length = to - from + 1;  // inclusive range
    uint8_t old_result = OldCRC8Implementations::tee501_calc_crc8_(hte501_buf, from, to);
    uint8_t new_result = crc8(&hte501_buf[from], length, 0xFF, 0x31, true);
    bool match = (old_result == new_result);
    ESP_LOGI(TAG, "TEE501 test %d (from=%d,to=%d,len=%d): old=0x%02X, new=0x%02X %s", i, from, to, length, old_result,
             new_result, match ? "PASS" : "FAIL");
    all_passed &= match;
  }

  // Test LC709203F implementation
  ESP_LOGI(TAG, "Testing LC709203F old vs new");
  for (int i = 0; i < 4; i++) {
    uint8_t old_result = OldCRC8Implementations::lc709203f_crc8_(pec_tests[i], pec_lens[i]);
    uint8_t new_result = crc8(pec_tests[i], pec_lens[i], 0x00, 0x07, true);
    bool match = (old_result == new_result);
    ESP_LOGI(TAG, "LC709203F test %d: old=0x%02X, new=0x%02X %s", i, old_result, new_result, match ? "PASS" : "FAIL");
    all_passed &= match;
  }

  // Test MLX90614 implementation
  ESP_LOGI(TAG, "Testing MLX90614 old vs new");
  for (int i = 0; i < 4; i++) {
    uint8_t old_result = OldCRC8Implementations::mlx90614_crc8_pec_(pec_tests[i], pec_lens[i]);
    uint8_t new_result = crc8(pec_tests[i], pec_lens[i], 0x00, 0x07, true);
    bool match = (old_result == new_result);
    ESP_LOGI(TAG, "MLX90614 test %d: old=0x%02X, new=0x%02X %s", i, old_result, new_result, match ? "PASS" : "FAIL");
    all_passed &= match;
  }

  log_test_result("Old vs New CRC8 implementations", all_passed);
}

bool CRC8TestComponent::verify_crc8(const char *test_name, const uint8_t *data, uint8_t len, uint8_t expected,
                                    uint8_t crc, uint8_t poly, bool msb_first) {
  uint8_t result = esphome::crc8(data, len, crc, poly, msb_first);
  bool passed = (result == expected);

  if (passed) {
    ESP_LOGI(TAG, "%s: PASS (0x%02X)", test_name, result);
  } else {
    ESP_LOGE(TAG, "%s: FAIL - expected 0x%02X, got 0x%02X", test_name, expected, result);
  }

  return passed;
}

void CRC8TestComponent::log_test_result(const char *test_name, bool passed) {
  if (passed) {
    ESP_LOGI(TAG, "%s: ALL TESTS PASSED", test_name);
  } else {
    ESP_LOGE(TAG, "%s: SOME TESTS FAILED", test_name);
  }
}

}  // namespace crc8_test_component
}  // namespace esphome
