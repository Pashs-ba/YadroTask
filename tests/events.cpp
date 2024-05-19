#include<gtest/gtest.h>
#include "lib/utils/data/Context.h"
#include "lib/utils/time_converter/TimeConverter.h"
#include "lib/events/IncomeEvent/IncomeEvent.h"
#include "lib/events/SitEvent/SitEvent.h"
#include "lib/events/WaitEvent/WaitEvent.h"
#include "lib/events/LeftEvent/LeftEvent.h"

class IncomeNotOpenTestSuite : public testing::TestWithParam<utils::data::Context> {
};

TEST_P(IncomeNotOpenTestSuite, IncomeNotOpenTest) {
  auto context = GetParam();
  auto event = std::make_unique<IncomeEvent>("10:00", "pass");
  auto result = event->submit(context);
  ASSERT_TRUE(result.has_value());
  std::stringstream ss;
  ss << *(result.value());
  ASSERT_EQ(ss.str(), "10:00 13 NotOpenYet");
}

INSTANTIATE_TEST_SUITE_P(IncomeNotOpenTest,
                         IncomeNotOpenTestSuite,
                         testing::Values(utils::data::Context{750, 1500, 0, {}},
                                         utils::data::Context{0, 100, 1000, {}}));

TEST(IncomeCilentExistTest, IncomeCilentExistTest) {
  utils::data::Context context{0, 1500, 0, {{true, 0}}};
  auto event = std::make_unique<IncomeEvent>("10:00", "pass");
  event->submit(context);
  auto result = event->submit(context);
  ASSERT_TRUE(result.has_value());
  std::stringstream ss;
  ss << *(result.value());
  ASSERT_EQ(ss.str(), "10:00 13 YouShallNotPass");
}

TEST(IncomeSuccessTest, IncomeSuccessTest) {
  utils::data::Context context{0, 1500, 0, {}};
  auto event = std::make_unique<IncomeEvent>("10:00", "pass");
  auto result = event->submit(context);
  ASSERT_FALSE(result.has_value());
  ASSERT_EQ(context.current_users.size(), 1);
  ASSERT_EQ(context.current_users["pass"], -1);
}

TEST(SitClientNotExistsTest, SitClientNotExistsTest) {
  utils::data::Context context{750, 1500, 0, {{true, 0}}};
  auto event2 = std::make_unique<SitEvent>("10:00", "pass2", 1);
  auto result2 = event2->submit(context);
  ASSERT_TRUE(result2.has_value());
  std::stringstream ss;
  ss << *(result2.value());
  ASSERT_EQ(ss.str(), "10:00 13 ClientDoesNotExist");
}

TEST(SitPlaceIsBusyTest, SitPlaceIsBusyTest) {
  utils::data::Context context{0, 1500, 0, {{true, 0}}};
  auto event = std::make_unique<IncomeEvent>("10:00", "pass");
  event->submit(context);
  auto event2 = std::make_unique<IncomeEvent>("10:00", "pass2");
  auto result2 = event2->submit(context);
  ASSERT_FALSE(result2.has_value());
  auto event3 = std::make_unique<SitEvent>("10:00", "pass2", 1);
  auto result3 = event3->submit(context);
  ASSERT_TRUE(result3.has_value());
  std::stringstream ss;
  ss << *(result3.value());
  ASSERT_EQ(ss.str(), "10:00 13 PlaceIsBusy");
}

TEST(SitSuccessTest, SitSuccessTest) {
  utils::data::Context context{0, 1500, 0, {{false, 0}}};
  auto event = std::make_unique<IncomeEvent>("10:00", "pass");
  event->submit(context);
  auto event2 = std::make_unique<SitEvent>("10:00", "pass", 1);
  auto result2 = event2->submit(context);
  ASSERT_FALSE(result2.has_value());
  ASSERT_EQ(context.tables[0].busy_from, 600);
  ASSERT_EQ(context.tables[0].busy, true);
  ASSERT_EQ(context.current_users["pass"], 0);
}

TEST(WaitClientUnknownTest, WaitClientUnknownTest) {
  utils::data::Context context{0, 1500, 0, {}};
  auto event = std::make_unique<WaitEvent>("10:00", "pass");
  auto result = event->submit(context);
  ASSERT_TRUE(result.has_value());
  std::stringstream ss;
  ss << *(result.value());
  ASSERT_EQ(ss.str(), "10:00 13 ClientUnknown");
}

TEST(WaitICanWaitNoLongerTest, WaitICanWaitNoLongerTest) {
  utils::data::Context context{0, 1500, 0, {{false, 0}}};
  auto event = std::make_unique<IncomeEvent>("10:00", "pass");
  event->submit(context);
  auto event2 = std::make_unique<WaitEvent>("10:00", "pass");
  auto result2 = event2->submit(context);
  ASSERT_TRUE(result2.has_value());
  std::stringstream ss;
  ss << *(result2.value());
  ASSERT_EQ(ss.str(), "10:00 13 ICanWaitNoLonger!");
}

TEST(WaitSuccessTest, WaitSuccessTest) {
  utils::data::Context context{0, 1500, 0, {{true, 0}}};
  auto event = std::make_unique<IncomeEvent>("10:00", "pass");
  event->submit(context);
  auto event2 = std::make_unique<WaitEvent>("10:00", "pass");
  auto result2 = event2->submit(context);
  ASSERT_FALSE(result2.has_value());
  ASSERT_EQ(context.queue.size(), 1);
  ASSERT_EQ(context.queue.front(), "pass");
}

TEST(WaitGoodbyeTest, WaitGoodbyeTest) {
  utils::data::Context context{0, 1500, 0, {{true, 0}}};
  auto event = std::make_unique<IncomeEvent>("10:00", "pass");
  event->submit(context);
  auto event2 = std::make_unique<IncomeEvent>("10:00", "pass2");
  event2->submit(context);
  auto event3 = std::make_unique<WaitEvent>("10:00", "pass");
  event3->submit(context);
  auto event4 = std::make_unique<WaitEvent>("10:00", "pass2");
  auto result4 = event4->submit(context);
  ASSERT_TRUE(result4.has_value());
  std::stringstream ss;
  ss << *(result4.value());
  ASSERT_EQ(ss.str(), "10:00 11 pass2");
}

TEST(LeftClientUnknownTest, LeftClientUnknownTest) {
  utils::data::Context context{0, 1500, 0, {}};
  auto event = std::make_unique<LeftEvent>("10:00", "pass");
  auto result = event->submit(context);
  ASSERT_TRUE(result.has_value());
  std::stringstream ss;
  ss << *(result.value());
  ASSERT_EQ(ss.str(), "10:00 13 ClientUnknown");
}

TEST(LeftSuccessNotSeatTest, LeftSuccessTest) {
  utils::data::Context context{0, 1500, 0, {{true, 0}}};
  auto event = std::make_unique<IncomeEvent>("10:00", "pass");
  event->submit(context);
  auto event3 = std::make_unique<LeftEvent>("10:00", "pass");
  auto result3 = event3->submit(context);
  ASSERT_FALSE(result3.has_value());
  ASSERT_EQ(context.tables[0].busy, true);
  ASSERT_EQ(context.current_users.size(), 0);
}

TEST(LeftSuccessSeatTest, LeftSuccessTest) {
  utils::data::Context context{0, 1500, 0, {{false, 0}}};
  auto event = std::make_unique<IncomeEvent>("10:00", "pass");
  event->submit(context);
  auto event2 = std::make_unique<SitEvent>("10:00", "pass", 1);
  event2->submit(context);
  auto event3 = std::make_unique<LeftEvent>("10:00", "pass");
  auto result3 = event3->submit(context);
  ASSERT_FALSE(result3.has_value());
  ASSERT_EQ(context.tables[0].busy, false);
  ASSERT_EQ(context.current_users.size(), 0);
}