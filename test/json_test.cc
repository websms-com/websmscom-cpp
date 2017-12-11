/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include <stdint.h>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "json.h"

namespace {

using namespace websms;

TEST(JsonTest, Serialize) {
  Json json;
  std::vector<int64_t> integer_array;
  integer_array.push_back(1);
  integer_array.push_back(2);
  json.Add("integer_array", integer_array);
  json.Add("integer", 1);
  json.Add("boolean", true);
  std::vector<std::string> string_array;
  string_array.push_back("String 1");
  string_array.push_back("String 2");
  json.Add("string_array", string_array);
  json.Add("string", "String");
  ASSERT_STREQ(json.GetAsString().c_str(), "{"
      "\"boolean\":true,"
      "\"integer\":1,"
      "\"integer_array\":[1,2],"
      "\"string\":\"String\","
      "\"string_array\":[\"String 1\",\"String 2\"]"
      "}");
}

TEST(JsonTest, Deserialize) {
  Json json;
  bool result = json.Parse("{"
      "\"boolean\":true,"
      "\"integer\":1,"
      "\"integer_array\":[1,2],"
      "\"string\":\"String\","
      "\"string_array\":[\"String 1\",\"String 2\"]"
      "}");
  ASSERT_TRUE(result);
  bool boolean_value;
  result = json.Get("invalid_boolean", &boolean_value);
  ASSERT_FALSE(result);
  result = json.Get("boolean", &boolean_value);
  ASSERT_TRUE(result);
  ASSERT_TRUE(boolean_value);
  int integer_value;
  result = json.Get("invalid_integer", &integer_value);
  ASSERT_FALSE(result);
  result = json.Get("integer", &integer_value);
  ASSERT_TRUE(result);
  ASSERT_EQ(integer_value, 1);
  const char* string_value;
  result = json.Get("invalid_string", &string_value);
  ASSERT_FALSE(result);
  result = json.Get("string", &string_value);
  ASSERT_TRUE(result);
  ASSERT_STREQ(string_value, "String");
  delete [] string_value;
}

TEST(JsonTest, DeserializeFailed) {
  Json json;
  bool result = json.Parse("Not a JSON string.");
  ASSERT_FALSE(result);
}

}  /* namespace */
