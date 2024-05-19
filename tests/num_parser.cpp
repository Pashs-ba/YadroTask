#include <gtest/gtest.h>
#include "lib/utils/time_converter/TimeConverter.h"
#include "lib/utils/NumParser.h"

class ValidFormatNumsTestSuite : public testing::TestWithParam<std::string> {
};

TEST_P(ValidFormatNumsTestSuite, ValidTest) {
  std::string param = GetParam();
  ASSERT_TRUE(utils::NumParser::from_chars<uint32_t>(param.data(),
                                                     param.data()+param.size()).has_value());
}

INSTANTIATE_TEST_SUITE_P(ValidFormatTest,
                         ValidFormatNumsTestSuite,
                         testing::Values("0", "1", "10", "100", "1000", "10000"));

class InvalidFormatNumsTestSuite : public testing::TestWithParam<std::string> {

};

TEST_P(InvalidFormatNumsTestSuite, InvalidTest) {
  std::string param = GetParam();
  ASSERT_FALSE(utils::NumParser::from_chars<uint32_t>(param.data(),
                                                      param.data()+param.size()).has_value());
}

INSTANTIATE_TEST_SUITE_P(InvalidFormatTest,
                         InvalidFormatNumsTestSuite,
                         testing::Values("a", "a1", "1a", "a1a", "1a1", "1 1", "1 1a", "a 1", "1 a", "-1", "  -10"));

class ValueCheckNumsTestSuite : public testing::TestWithParam<std::tuple<std::string, uint32_t>> {

};

TEST_P(ValueCheckNumsTestSuite, ValueCheckTest) {
  auto [param, expected] = GetParam();
  ASSERT_EQ(utils::NumParser::from_chars<uint32_t>(param.data(),
                                                   param.data()+param.size()).value(), expected);
}

INSTANTIATE_TEST_SUITE_P(ValueCheckTest,
                         ValueCheckNumsTestSuite,
                         testing::Values(std::make_tuple("0", 0),
                                         std::make_tuple("1", 1),
                                         std::make_tuple("10", 10),
                                         std::make_tuple("100", 100),
                                         std::make_tuple("1000", 1000),
                                         std::make_tuple("10000", 10000)));