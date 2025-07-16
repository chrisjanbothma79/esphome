#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Include here headers related to the esphome component you are testing:
// #include "esphome/components/uart/uart_component.h"

// Now you can instantiate the component manually and write Google Tests:
TEST(ExampleTest, test1) {
  EXPECT_EQ(1, 1);
  EXPECT_NE(0, 1);
}
