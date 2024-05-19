#include <gtest/gtest.h>
#include <tuple>
#include "lib/utils/time_converter/TimeConverter.h"

class ValidFormatTimeTestSuite : public testing::TestWithParam<std::string> {
};

TEST_P(ValidFormatTimeTestSuite, ValidTest) {
  std::string param = GetParam();
  ASSERT_TRUE(utils::TimeConverter::toMinutes(param).has_value());
}

INSTANTIATE_TEST_SUITE_P(ValidFormatTest,
                         ValidFormatTimeTestSuite,
                         testing::Values("00:00", "23:59", "12:00", "01:00", "10:01", "20:20"));

class InvalidFormatTimeTestSuite : public testing::TestWithParam<std::string> {

};

TEST_P(InvalidFormatTimeTestSuite, InvalidTest) {
  std::string param = GetParam();
  ASSERT_FALSE(utils::TimeConverter::toMinutes(param).has_value());
}

INSTANTIATE_TEST_SUITE_P(InvalidFormatTest,
                         InvalidFormatTimeTestSuite,
                         testing::Values("24:00",
                                         "00:60",
                                         "25:00",
                                         "00:61",
                                         "12:61",
                                         "13:60",
                                         "aa",
                                         "3:40",
                                         "04:2",
                                         "234",
                                         "12:30 ",
                                         " 11:21",
                                         "12:30:40",
                                         "11 : 21"));

class ValueCheckTimeTestSuite : public testing::TestWithParam<std::tuple<std::string, int32_t>> {

};

TEST_P(ValueCheckTimeTestSuite, ValueCheckTest) {
  auto [param, expected] = GetParam();
  ASSERT_EQ(utils::TimeConverter::toMinutes(param).value(), expected);
}

INSTANTIATE_TEST_SUITE_P(ValueCheckTest,
                         ValueCheckTimeTestSuite,
                         testing::Values(std::make_tuple("00:00", 0),
                                         std::make_tuple("23:59", 1439),
                                         std::make_tuple("12:00", 720),
                                         std::make_tuple("01:00", 60),
                                         std::make_tuple("10:01", 601),
                                         std::make_tuple("20:20", 1220)));