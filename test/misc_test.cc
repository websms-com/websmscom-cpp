/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include "gtest/gtest.h"
#include <websms/misc.h>

namespace {

using namespace websms;

TEST(MiscTest, SenderAddressTypeToString) {
  ASSERT_STREQ(SenderAddressTypeToString(kNational), "national");
  ASSERT_STREQ(SenderAddressTypeToString(kInternational), "international");
  ASSERT_STREQ(SenderAddressTypeToString(kAlphanumeric), "alphanumeric");
  ASSERT_STREQ(SenderAddressTypeToString(kShortcode), "shortcode");
  ASSERT_FALSE(SenderAddressTypeToString(SenderAddressType(9999)));
}

TEST(MiscTest, Strdup) {
  const char* text = "This is a test.";
  const char* copy = Strdup(text);
  ASSERT_TRUE(copy);
  ASSERT_NE(text, copy);
  ASSERT_STREQ(text, copy);
  delete [] copy;
}

}  /* namespace */
