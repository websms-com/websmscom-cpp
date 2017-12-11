/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include <iostream>
#include <string>

#include "gtest/gtest.h"

#include <websms/exceptions.h>
#include <websms/sms_client.h>
#include <websms/status_codes.h>

#include "utils.h"

namespace {

using namespace websms;

TEST(SmsClientTest, InvalidUrl) {
  SmsClient client("user", "password", "Not an url.");
  TextMessage message(1234567, "Text message");
  ASSERT_THROW(client.Send(message, 1, true), HttpConnectionException);
}

TEST(SmsClientTest, AuthorizationFailed) {
  SmsClient client("user", "password", GetUrl());
  TextMessage message(1234567, "Text message");
  ASSERT_THROW(client.Send(message, 1, true), AuthorizationFailedException);
}

TEST(SmsClientTest, ApiException) {
  bool ok = true;
  const char* user = GetUsername(&ok);
  const char* pass = GetPassword(&ok);
  if (ok) {
    SmsClient client(user, pass, GetUrl());
    TextMessage message(1234567, "");
    ASSERT_THROW(client.Send(message, 1, true), ApiException);
  }
}

TEST(SmsClientTest, SendTextTestOk) {
  bool ok = true;
  const char* user = GetUsername(&ok);
  const char* pass = GetPassword(&ok);
  if (ok) {
    SmsClient client(user, pass, GetUrl());
    TextMessage message(1234567, "Text message");
    message.set_client_message_id("client_message_id");
    MessageResponse response = client.Send(message, 1, true);
    ASSERT_EQ(response.status_code(), kOk);
    ASSERT_STREQ(response.status_message(), "OK");
    ASSERT_TRUE(response.transfer_id());
    ASSERT_STREQ(response.client_message_id(), "client_message_id");
  }
}

TEST(SmsClientTest, SendBinaryTestOk) {
  bool ok = true;
  const char* user = GetUsername(&ok);
  const char* pass = GetPassword(&ok);
  if (ok) {
    SmsClient client(user, pass, GetUrl());
    AddressList recipients(1);
    recipients[0] = 1234567;
    uint8_t data[] = { 0x00, 0x01, 0x02 };
    BinaryData binary_content(1);
    binary_content.Set(0, data, 3);
    BinaryMessage message(recipients, binary_content);
    message.set_user_data_header_present(true);
    message.set_client_message_id("client_message_id");
    MessageResponse response = client.Send(message, true);
    ASSERT_EQ(response.status_code(), kOk);
    ASSERT_STREQ(response.status_message(), "OK");
    ASSERT_TRUE(response.transfer_id());
    ASSERT_STREQ(response.client_message_id(), "client_message_id");
  }
}

}  /* namespace */
