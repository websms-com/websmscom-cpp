/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include <stdint.h>

#include "gtest/gtest.h"

#include "websms/arrays.h"

namespace {

using namespace websms;

TEST(ArrayUtilTest, Create) {
  Uint8Array* array = ArrayUtil::Create<Uint8Array>(3);
  ASSERT_EQ(array->size, 3U);
  ASSERT_TRUE(array->array);
  ASSERT_EQ(array->array[0], 0);
  ASSERT_EQ(array->array[1], 0);
  ASSERT_EQ(array->array[2], 0);
  ArrayUtil::Destroy(array);
}

TEST(ArrayUtilTest, CreateZeroSizeArray) {
  Uint8Array* array = ArrayUtil::Create<Uint8Array>(static_cast<size_t>(0));
  ASSERT_EQ(array->size, 0U);
  ASSERT_FALSE(array->array);
  ArrayUtil::Destroy(array);
}

TEST(ArrayUtilTest, Copy) {
  Uint8Array* source = ArrayUtil::Create<Uint8Array>(3);
  source->array[0] = 0;
  source->array[1] = 1;
  source->array[2] = 2;
  Uint8Array* target = ArrayUtil::Copy(source);
  ASSERT_EQ(target->size, 3U);
  ASSERT_TRUE(target->array);
  ASSERT_EQ(target->array[0], 0);
  ASSERT_EQ(target->array[1], 1);
  ASSERT_EQ(target->array[2], 2);
  target->array[0] = 2;
  target->array[1] = 1;
  target->array[2] = 0;
  ASSERT_EQ(source->array[0], 0);
  ASSERT_EQ(source->array[1], 1);
  ASSERT_EQ(source->array[2], 2);
  ASSERT_EQ(target->array[0], 2);
  ASSERT_EQ(target->array[1], 1);
  ASSERT_EQ(target->array[2], 0);
  ArrayUtil::Destroy(source);
  ArrayUtil::Destroy(target);
}

}  /* namespace */
