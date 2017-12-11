/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include "gtest/gtest.h"

#include <websms/misc.h>
#include <websms/requests.h>

namespace {

using namespace websms;

TEST(RequestsTest, TextSmsSendRequestCreate) {
  TextSmsSendRequest* request = TextSmsSendRequest::Create();
  ASSERT_TRUE(request);
  ASSERT_FALSE(request->message_content);
  ASSERT_EQ(request->max_sms_per_message, 1);
  ASSERT_TRUE(request->test);
  ASSERT_FALSE(request->recipient_address_list);
  ASSERT_FALSE(request->sender_address);
  ASSERT_STREQ(request->sender_address_type,
               SenderAddressTypeToString(kNational));
  ASSERT_FALSE(request->send_as_flash_sms);
  ASSERT_FALSE(request->notification_callback_url);
  ASSERT_FALSE(request->client_message_id);
  ASSERT_FALSE(request->priority);
  ASSERT_FALSE(request->auth_token);
  ASSERT_FALSE(request->api_key);
  TextSmsSendRequest::Destroy(request);
}

TEST(RequestsTest, TextSmsSendRequestCopy) {
  TextSmsSendRequest* request = TextSmsSendRequest::Create();
  request->message_content = Strdup("message_content");
  request->max_sms_per_message = 2;
  request->test = true;
  request->recipient_address_list = ArrayUtil::Create<Int64Array>(1);
  request->recipient_address_list->array[0] = 1234;
  Strdel(request->sender_address_type);
  request->sender_address = Strdup("sender_address");
  request->sender_address_type =
      Strdup(SenderAddressTypeToString(kInternational));
  request->send_as_flash_sms = true;
  request->notification_callback_url = Strdup("notification_callback_url");
  request->client_message_id = Strdup("client_message_id");
  request->priority = 2;
  request->auth_token = Strdup("auth_token");
  request->api_key = Strdup("api_key");
  TextSmsSendRequest* copy = TextSmsSendRequest::Copy(request);
  ASSERT_TRUE(copy);
  ASSERT_STREQ(copy->message_content, "message_content");
  ASSERT_NE(copy->message_content, request->message_content);
  ASSERT_EQ(copy->max_sms_per_message, 2);
  ASSERT_TRUE(copy->test);
  ASSERT_TRUE(copy->recipient_address_list);
  ASSERT_TRUE(copy->recipient_address_list->array);
  ASSERT_EQ(copy->recipient_address_list->size, 1U);
  ASSERT_EQ(copy->recipient_address_list->array[0], 1234);
  ASSERT_NE(copy->recipient_address_list->array,
            request->recipient_address_list->array);
  ASSERT_NE(copy->recipient_address_list, request->recipient_address_list);
  ASSERT_STREQ(copy->sender_address, "sender_address");
  ASSERT_NE(copy->sender_address, request->sender_address);
  ASSERT_STREQ(copy->sender_address_type, "international");
  ASSERT_NE(copy->sender_address_type, request->sender_address_type);
  ASSERT_TRUE(copy->send_as_flash_sms);
  ASSERT_STREQ(copy->notification_callback_url, "notification_callback_url");
  ASSERT_NE(copy->notification_callback_url, request->notification_callback_url);
  ASSERT_STREQ(copy->client_message_id, "client_message_id");
  ASSERT_NE(copy->client_message_id, request->client_message_id);
  ASSERT_EQ(copy->priority, 2U);
  ASSERT_STREQ(copy->auth_token, "auth_token");
  ASSERT_NE(copy->auth_token, request->auth_token);
  ASSERT_STREQ(copy->api_key, "api_key");
  ASSERT_NE(copy->api_key, request->api_key);
  TextSmsSendRequest::Destroy(copy);
  TextSmsSendRequest::Destroy(request);
}

TEST(RequestsTest, TextSmsSendRequestSerialize) {
  TextSmsSendRequest* request = TextSmsSendRequest::Create();
  request->message_content = Strdup("message_content");
  request->max_sms_per_message = 2;
  request->test = true;
  request->recipient_address_list = ArrayUtil::Create<Int64Array>(1);
  request->recipient_address_list->array[0] = 1234;
  Strdel(request->sender_address_type);
  request->sender_address = Strdup("sender_address");
  request->sender_address_type =
      Strdup(SenderAddressTypeToString(kInternational));
  request->send_as_flash_sms = true;
  request->notification_callback_url = Strdup("notification_callback_url");
  request->client_message_id = Strdup("client_message_id");
  request->priority = 2;
  request->auth_token = Strdup("auth_token");
  request->api_key = Strdup("api_key");
  const char* result = TextSmsSendRequest::Serialize(request);
  ASSERT_STREQ(result, "{"
      "\"priority\":2,"
      "\"senderAddress\":\"sender_address\","
      "\"authToken\":\"auth_token\","
      "\"maxSmsPerMessage\":2,"
      "\"messageContent\":\"message_content\","
      "\"notificationCallbackUrl\":\"notification_callback_url\","
      "\"senderAddressType\":\"international\","
      "\"recipientAddressList\":[1234],"
      "\"apiKey\":\"api_key\","
      "\"test\":true,"
      "\"sendAsFlashSms\":true,"
      "\"clientMessageId\":\"client_message_id\""
      "}");
  TextSmsSendRequest::Destroy(request);
  delete [] result;
}

TEST(RequestsTest, TextSmsSendRequestDeserialize) {
  TextSmsSendRequest* request = TextSmsSendRequest::Create();
  const char* data = NULL;
  bool result = TextSmsSendRequest::Deserialize(data, request);
  ASSERT_FALSE(result);
  TextSmsSendRequest::Destroy(request);
}

TEST(RequestsTest, BinarySmsSendRequestCreate) {
  BinarySmsSendRequest* request = BinarySmsSendRequest::Create();
  ASSERT_TRUE(request);
  ASSERT_FALSE(request->user_data_header_present);
  ASSERT_FALSE(request->message_content);
  ASSERT_TRUE(request->test);
  ASSERT_FALSE(request->recipient_address_list);
  ASSERT_FALSE(request->sender_address);
  ASSERT_STREQ(request->sender_address_type,
               SenderAddressTypeToString(kNational));
  ASSERT_FALSE(request->send_as_flash_sms);
  ASSERT_FALSE(request->notification_callback_url);
  ASSERT_FALSE(request->client_message_id);
  ASSERT_FALSE(request->priority);
  ASSERT_FALSE(request->auth_token);
  ASSERT_FALSE(request->api_key);
  BinarySmsSendRequest::Destroy(request);
}

TEST(RequestsTest, BinarySmsSendRequestCopy) {
  BinarySmsSendRequest* request = BinarySmsSendRequest::Create();
  request->user_data_header_present = true;
  request->message_content = ArrayUtil::Create<BinaryArray>(1);
  request->message_content->array[0] = ArrayUtil::Create<Uint8Array>(3);
  request->message_content->array[0]->array[0] = 0;
  request->message_content->array[0]->array[1] = 1;
  request->message_content->array[0]->array[2] = 2;
  request->test = true;
  request->recipient_address_list = ArrayUtil::Create<Int64Array>(1);
  request->recipient_address_list->array[0] = 1234;
  Strdel(request->sender_address_type);
  request->sender_address = Strdup("sender_address");
  request->sender_address_type =
      Strdup(SenderAddressTypeToString(kInternational));
  request->send_as_flash_sms = true;
  request->notification_callback_url = Strdup("notification_callback_url");
  request->client_message_id = Strdup("client_message_id");
  request->priority = 2;
  request->auth_token = Strdup("auth_token");
  request->api_key = Strdup("api_key");
  BinarySmsSendRequest* copy = BinarySmsSendRequest::Copy(request);
  ASSERT_TRUE(copy);
  ASSERT_TRUE(copy->user_data_header_present);
  ASSERT_TRUE(copy->message_content);
  ASSERT_TRUE(copy->message_content->array);
  ASSERT_TRUE(copy->message_content->array[0]->array);
  ASSERT_EQ(copy->message_content->size, 1U);
  ASSERT_EQ(copy->message_content->array[0]->size, 3U);
  ASSERT_EQ(copy->message_content->array[0]->array[0], 0);
  ASSERT_EQ(copy->message_content->array[0]->array[1], 1);
  ASSERT_EQ(copy->message_content->array[0]->array[2], 2);
  ASSERT_NE(copy->message_content, request->message_content);
  ASSERT_NE(copy->message_content->array, request->message_content->array);
  ASSERT_NE(copy->message_content->array[0]->array,
            request->message_content->array[0]->array);
  ASSERT_NE(copy->message_content, request->message_content);
  ASSERT_TRUE(copy->test);
  ASSERT_TRUE(copy->recipient_address_list);
  ASSERT_TRUE(copy->recipient_address_list->array);
  ASSERT_EQ(copy->recipient_address_list->size, 1U);
  ASSERT_EQ(copy->recipient_address_list->array[0], 1234);
  ASSERT_NE(copy->recipient_address_list->array,
            request->recipient_address_list->array);
  ASSERT_NE(copy->recipient_address_list, request->recipient_address_list);
  ASSERT_STREQ(copy->sender_address, "sender_address");
  ASSERT_NE(copy->sender_address, request->sender_address);
  ASSERT_STREQ(copy->sender_address_type, "international");
  ASSERT_NE(copy->sender_address_type, request->sender_address_type);
  ASSERT_TRUE(copy->send_as_flash_sms);
  ASSERT_STREQ(copy->notification_callback_url, "notification_callback_url");
  ASSERT_NE(copy->notification_callback_url, request->notification_callback_url);
  ASSERT_STREQ(copy->client_message_id, "client_message_id");
  ASSERT_NE(copy->client_message_id, request->client_message_id);
  ASSERT_EQ(copy->priority, 2U);
  ASSERT_STREQ(copy->auth_token, "auth_token");
  ASSERT_NE(copy->auth_token, request->auth_token);
  ASSERT_STREQ(copy->api_key, "api_key");
  ASSERT_NE(copy->api_key, request->api_key);
  BinarySmsSendRequest::Destroy(copy);
  BinarySmsSendRequest::Destroy(request);
}

TEST(RequestsTest, BinarySmsSendRequestSerialize) {
  BinarySmsSendRequest* request = BinarySmsSendRequest::Create();
  request->user_data_header_present = true;
  request->message_content = ArrayUtil::Create<BinaryArray>(1);
  request->message_content->array[0] = ArrayUtil::Create<Uint8Array>(3);
  request->message_content->array[0]->array[0] = 0;
  request->message_content->array[0]->array[1] = 1;
  request->message_content->array[0]->array[2] = 2;
  request->test = true;
  request->recipient_address_list = ArrayUtil::Create<Int64Array>(1);
  request->recipient_address_list->array[0] = 1234;
  Strdel(request->sender_address_type);
  request->sender_address = Strdup("sender_address");
  request->sender_address_type =
      Strdup(SenderAddressTypeToString(kInternational));
  request->send_as_flash_sms = true;
  request->notification_callback_url = Strdup("notification_callback_url");
  request->client_message_id = Strdup("client_message_id");
  request->priority = 2;
  request->auth_token = Strdup("auth_token");
  request->api_key = Strdup("api_key");
  const char* result = BinarySmsSendRequest::Serialize(request);
  ASSERT_STREQ(result, "{"
      "\"apiKey\":\"api_key\","
      "\"test\":true,"
      "\"userDataHeaderPresent\":true,"
      "\"priority\":2,"
      "\"senderAddress\":\"sender_address\","
      "\"messageContent\":[\"AAEC\"],"
      "\"notificationCallbackUrl\":\"notification_callback_url\","
      "\"senderAddressType\":\"international\","
      "\"recipientAddressList\":[1234],"
      "\"sendAsFlashSms\":true,"
      "\"clientMessageId\":\"client_message_id\","
      "\"authToken\":\"auth_token\""
      "}");
  BinarySmsSendRequest::Destroy(request);
  delete [] result;
}

TEST(RequestsTest, BinarySmsSendRequestDeserialize) {
  BinarySmsSendRequest* request = BinarySmsSendRequest::Create();
  const char* data = NULL;
  bool result = BinarySmsSendRequest::Deserialize(data, request);
  ASSERT_FALSE(result);
  BinarySmsSendRequest::Destroy(request);
}

}  /* namespace */
