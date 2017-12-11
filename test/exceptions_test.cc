/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include "gtest/gtest.h"

#include <websms/exceptions.h>

namespace {

using namespace websms;

TEST(ExceptionsTest, Exception) {
  Exception ex1("Test");
  ASSERT_EQ(ex1.error_code(), 0);
  ASSERT_STREQ(ex1.message(), "Test");
  ASSERT_STREQ(ex1.What(), "Test");
  Exception ex2("Test", 1);
  ASSERT_EQ(ex2.error_code(), 1);
  ASSERT_STREQ(ex2.message(), "Test");
  ASSERT_STREQ(ex2.What(), "Test");
}

TEST(ExceptionsTest, ApiException) {
  ApiException ex1("Test", 1);
  ASSERT_EQ(ex1.status_code(), 1);
  ASSERT_STREQ(ex1.status_message(), "Test");
}

TEST(ExceptionsTest, HttpConnectionException) {
  HttpConnectionException ex1("Test", 1);
  ASSERT_EQ(ex1.error_code(), 1);
  ASSERT_STREQ(ex1.message(), "Test");
}

TEST(ExceptionsTest, ParameterValidationException) {
  ParameterValidationException ex1("Test");
  ASSERT_EQ(ex1.error_code(), 0);
  ASSERT_STREQ(ex1.message(), "Test");
}

}  /* namespace */
