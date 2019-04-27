#include "ref_counter.h"
#include "gtest/gtest.h"

TEST(RefCounter, keep__should_increase_reference_count) {
  lib::RefCounter rc;

  rc.keep();

  ASSERT_EQ(rc.release(), 1);
}

TEST(RefCounter, release__should_return_0_without_any_keep_call) {
  lib::RefCounter rc;

  ASSERT_EQ(rc.release(), 0);
}

TEST(RefCounter, release__should_never_return_negative_number) {
  lib::RefCounter rc;

  rc.release();

  ASSERT_EQ(rc.release(), 0);
}