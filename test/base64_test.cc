/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include <stdint.h>
#include <string>

#include "gtest/gtest.h"
#include "base64.h"

namespace {

using namespace websms;

TEST(Base64Test, TextEncode) {
  std::string encoded = Base64::Encode<std::string>("Just a test string.");
  ASSERT_STREQ(encoded.c_str(), "SnVzdCBhIHRlc3Qgc3RyaW5nLg==");
}

TEST(Base64Test, TextDecode) {
  std::string decoded;
  std::string* result;
  result = Base64::Decode<std::string>("SnVzdCBhIHRlc3Qgc3RyaW5nLg==",
                                       &decoded);
  ASSERT_TRUE(result);
  ASSERT_EQ(result, &decoded);
  ASSERT_STREQ(decoded.c_str(), "Just a test string.");
}

TEST(Base64Test, BinaryEncode) {
  std::vector<uint8_t> data;
  data.push_back(0);
  data.push_back(1);
  data.push_back(2);
  std::string encoded = Base64::Encode<std::vector<uint8_t> >(data);
  ASSERT_STREQ(encoded.c_str(), "AAEC");
}

TEST(Base64Test, BinaryDecode) {
  std::vector<uint8_t> decoded;
  std::vector<uint8_t>* result;
  result = Base64::Decode<std::vector<uint8_t> >("AAEC", &decoded);
  ASSERT_TRUE(result);
  ASSERT_EQ(result, &decoded);
  ASSERT_EQ(decoded.size(), 3U);
  ASSERT_EQ(decoded[0], 0);
  ASSERT_EQ(decoded[1], 1);
  ASSERT_EQ(decoded[2], 2);
}

TEST(Base64Test, DecodeFailed) {
  std::string decoded;
  std::string* result;
  result = Base64::Decode<std::string>("Not Base64 encoded.", &decoded);
  ASSERT_FALSE(result);
}

}  /* namespace */
