/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include "gtest/gtest.h"

#include <websms/misc.h>
#include <websms/responses.h>
#include <websms/status_codes.h>

namespace {

using namespace websms;

TEST(ResponsesTest, SmsSendResponseCreate) {
  SmsSendResponse* response = SmsSendResponse::Create();
  ASSERT_TRUE(response);
  ASSERT_FALSE(response->client_message_id);
  ASSERT_FALSE(response->transfer_id);
  ASSERT_EQ(response->status_code, 2000);
  ASSERT_FALSE(response->status_message);
  SmsSendResponse::Destroy(response);
}

TEST(ResponsesTest, SmsSendResponseCopy) {
  SmsSendResponse* response = SmsSendResponse::Create();
  response->client_message_id = Strdup("client_message_id");
  response->transfer_id = Strdup("transfer_id");
  response->status_code = kOkTest;
  response->status_message = Strdup("status_message");
  SmsSendResponse* copy = SmsSendResponse::Copy(response);
  ASSERT_TRUE(copy);
  ASSERT_NE(copy, response);
  ASSERT_STREQ(copy->client_message_id, "client_message_id");
  ASSERT_NE(copy->client_message_id, response->client_message_id);
  ASSERT_STREQ(copy->transfer_id, "transfer_id");
  ASSERT_NE(copy->transfer_id, response->transfer_id);
  ASSERT_EQ(copy->status_code, 2002);
  ASSERT_STREQ(copy->status_message, "status_message");
  ASSERT_NE(copy->status_message, response->status_message);
  SmsSendResponse::Destroy(response);
  SmsSendResponse::Destroy(copy);
}

TEST(ResponsesTest, SmsSendResponseSerialize) {
  SmsSendResponse* response = SmsSendResponse::Create();
  response->client_message_id = Strdup("client_message_id");
  response->transfer_id = Strdup("transfer_id");
  response->status_code = kOkTest;
  response->status_message = Strdup("status_message");
  const char* result = SmsSendResponse::Serialize(response);
  ASSERT_STREQ(result, "{"
      "\"clientMessageId\":\"client_message_id\","
      "\"transferId\":\"transfer_id\","
      "\"statusCode\":2002,"
      "\"statusMessage\":\"status_message\""
      "}");
  SmsSendResponse::Destroy(response);
  delete [] result;
}

TEST(ResponsesTest, SmsSendResponseDeserialize) {
  SmsSendResponse* response = SmsSendResponse::Create();
  const char* data = "{"
      "\"clientMessageId\":\"client_message_id\","
      "\"transferId\":\"transfer_id\","
      "\"statusCode\":2002,"
      "\"statusMessage\":\"status_message\""
      "}";
  bool result = SmsSendResponse::Deserialize(data, response);
  ASSERT_TRUE(result);
  ASSERT_STREQ(response->client_message_id, "client_message_id");
  ASSERT_STREQ(response->transfer_id, "transfer_id");
  ASSERT_EQ(response->status_code, 2002);
  ASSERT_STREQ(response->status_message, "status_message");
  SmsSendResponse::Destroy(response);
}

TEST(ResponsesTest, SmsSendResponseDeserializeFailed) {
  SmsSendResponse* response = SmsSendResponse::Create();
  bool result = SmsSendResponse::Deserialize("Invalid data.", response);
  ASSERT_FALSE(result);
  SmsSendResponse::Destroy(response);
}

}  /* namespace */
