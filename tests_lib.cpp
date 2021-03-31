#include "gtest/gtest.h"

extern "C" {
#include "search.h"
#include "enum.h"
}

TEST(find_max_seq, first) {
  char buf[] = "abbk\"c\"Kla\"7\"v";
  Seq seq = {buf, 14};
  StartEnd st_e_waited = {6, 12};
  StartEnd st_e_returned = find_max_seq(seq);
  ASSERT_EQ(st_e_waited.start, st_e_returned.start);
  ASSERT_EQ(st_e_waited.end, st_e_returned.end);
}

TEST(find_max_seq, first_one_more) {
  char buf[] = "abb9k\"c\"Kla\"7\"v";
  Seq seq = {buf, 15};
  StartEnd st_e_waited = {7, 13};
  StartEnd st_e_returned = find_max_seq(seq);
  ASSERT_EQ(st_e_waited.start, st_e_returned.start);
  ASSERT_EQ(st_e_waited.end, st_e_returned.end);
}

TEST(find_max_seq, no_res) {
  char buf[] = "jkhjgasdGHJ78";
  Seq seq = {buf, 13};
  StartEnd st_e_waited = {-1, -1};
  StartEnd st_e_returned = find_max_seq(seq);
  ASSERT_EQ(st_e_waited.start, st_e_returned.start);
  ASSERT_EQ(st_e_waited.end, st_e_returned.end);
}

TEST(find_max_seq, only_end) {
  char buf[] = "jkhjga\"sdGHJ78";
  Seq seq = {buf, 14};
  StartEnd st_e_waited = {-1, 6};
  StartEnd st_e_returned = find_max_seq(seq);
  ASSERT_EQ(st_e_waited.start, st_e_returned.start);
  ASSERT_EQ(st_e_waited.end, st_e_returned.end);
}

TEST(find_max_seq, only_start) {
  char buf[] = "jkhjga\"SdGHJ78";
  Seq seq = {buf, 14};
  StartEnd st_e_waited = {6, 6};
  StartEnd st_e_returned = find_max_seq(seq);
  ASSERT_EQ(st_e_waited.start, st_e_returned.start);
  ASSERT_EQ(st_e_waited.end, st_e_returned.end);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
