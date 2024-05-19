#include<gtest/gtest.h>
#include<lib/parser/Parser.h>

class InvalidManagerConfigTestSuite : public testing::TestWithParam<std::tuple<
    std::string,
    std::string,
    std::string,
    std::string>> {

};

TEST_P(InvalidManagerConfigTestSuite, InvalidTest) {
  auto [table_count, times, cost_of_hour, error] = GetParam();
  auto res = Parser::parse_manager_config(
      table_count,
      times,
      cost_of_hour);
  ASSERT_TRUE(std::holds_alternative<std::string>(res));
  ASSERT_EQ(std::get<std::string>(res), error);
}

INSTANTIATE_TEST_SUITE_P(InvalidManagerConfigTest,
                         InvalidManagerConfigTestSuite,
                         testing::Values(
                             std::make_tuple("-1", "00:00 01:01", "12", "-1"),
                             std::make_tuple("aaa", "00:00 01:01", "12", "aaa"),
                             std::make_tuple("1", "00:0001:01", "12", "00:0001:01"),
                             std::make_tuple("1", "00:00 ", "12a", "00:00 "),
                             std::make_tuple("1", "00:00 01:01", "12a", "12a"),
                             std::make_tuple("1", "01:01 00:00", "12", "01:01 00:00")));

class ValidManagerConfigTestSuite : public testing::TestWithParam<std::tuple<std::string,
                                                                             std::string,
                                                                             std::string>> {
};
TEST_P(ValidManagerConfigTestSuite, ValidTest) {
  auto [table_count, times, cost_of_hour] = GetParam();
  auto res = Parser::parse_manager_config(
      table_count,
      times,
      cost_of_hour);
  ASSERT_TRUE(std::holds_alternative<Manager>(res));
}

INSTANTIATE_TEST_SUITE_P(ValidManagerConfigTest,
                         ValidManagerConfigTestSuite,
                         testing::Values(
                             std::make_tuple("1", "00:00 01:01", "12"),
                             std::make_tuple("100", "00:00 01:01", "12"),
                             std::make_tuple("100", "00:00 01:01", "1200")));

class InvalidEventTestSuite : public testing::TestWithParam<std::string> {

};

TEST_P(InvalidEventTestSuite, InvalidTest) {
  auto res = Parser::parse_event(GetParam());
  ASSERT_FALSE(res.has_value());
}

INSTANTIATE_TEST_SUITE_P(InvalidEventTest,
                         InvalidEventTestSuite,
                         testing::Values("",
                                         "1",
                                         "00:00",
                                         "00:00 1",
                                         "00:00 1 1 ss",
                                         "00:00 1 pashs#ba",
                                         "00:00 2 1",
                                         "00:00 2 pashs#ba",
                                         "00:00 2 pashs#ba pashs.ba",
                                         "00:00 3 1 ss",
                                         "00:00 3 pashs#ba",
                                         "00:00 3 pashs#ba pashs.ba",
                                         "00:00 4 1 ss",
                                         "00:00 4 pashs#ba",
                                         "00:00 4 pashs#ba pashs.ba"));

class ValidEventTestSuite : public testing::TestWithParam<std::string> {

};

TEST_P(ValidEventTestSuite, ValidTest) {
  auto res = Parser::parse_event(GetParam());
  ASSERT_TRUE(res.has_value());
}

INSTANTIATE_TEST_SUITE_P(ValidEventTest,
                         ValidEventTestSuite,
                         testing::Values("00:00 1 pashsba",
                                         "00:00 1 11",
                                         "00:00 2 pashsba 22",
                                         "00:00 3 pashsba",
                                         "00:00 4 pashsba"));

