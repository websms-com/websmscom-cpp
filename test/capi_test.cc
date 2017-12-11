/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include "gtest/gtest.h"

#include <websms/capi.h>

#include "utils.h"

namespace {

using namespace websms;

TEST(CapiTest, CreateSmsClientContext) {
  SmsClientContext* context = CreateSmsClientContext("user", "pass", "url");
  ASSERT_STREQ(context->username, "user");
  ASSERT_STREQ(context->password, "pass");
  ASSERT_STREQ(context->url, "url");
  FreeSmsClientContext(context);
}

TEST(CapiTest, CreateTextSmsSendRequest) {
  TextSmsSendRequest* request = CreateTextSmsSendRequest();
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
  FreeTextSmsSendRequest(request);
}

TEST(CapiTest, CreateBinarySmsSendRequest) {
  BinarySmsSendRequest* request = CreateBinarySmsSendRequest();
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
  FreeBinarySmsSendRequest(request);
}

TEST(CapiTest, CreateInt64Array) {
  Int64Array* array = CreateInt64Array(3);
  ASSERT_TRUE(array);
  ASSERT_EQ(array->size, 3U);
  ASSERT_TRUE(array->array);
  ASSERT_EQ(array->array[0], 0);
  ASSERT_EQ(array->array[1], 0);
  ASSERT_EQ(array->array[2], 0);
  FreeInt64Array(array);
}

TEST(CapiTest, CreateUint8Array) {
  uint8_t data[] = { 0x00, 0x01, 0x02 };
  Uint8Array* array = CreateUint8Array(data, 3);
  ASSERT_TRUE(array);
  ASSERT_EQ(array->size, 3U);
  ASSERT_TRUE(array->array);
  ASSERT_EQ(array->array[0], 0x00);
  ASSERT_EQ(array->array[1], 0x01);
  ASSERT_EQ(array->array[2], 0x02);
  FreeUint8Array(array);
}

TEST(CapiTest, CreateBinaryArray) {
  BinaryArray* array = CreateBinaryArray(1);
  ASSERT_TRUE(array);
  ASSERT_EQ(array->size, 1U);
  ASSERT_TRUE(array->array);
  FreeBinaryArray(array);
}

TEST(CapiTest, SendTextMessage) {
  bool ok = true;
  const char* user = GetUsername(&ok);
  const char* pass = GetPassword(&ok);
  if (ok) {
    SmsClientContext* context = CreateSmsClientContext(user, pass, GetUrl());
    Int64Array* addresses = CreateInt64Array(1);
    addresses->array[0] = 1234567;
    TextSmsSendRequest* request  = CreateTextSmsSendRequest();
    request->message_content = Strdup(UTF8("Test"));
    request->recipient_address_list = addresses;
    request->test = 1;
    request->client_message_id = Strdup("client_message_id");
    int error_code;
    SmsSendResponse* response = SendTextMessage(context, request, &error_code);
    ASSERT_EQ(error_code, 0);
    ASSERT_EQ(response->status_code, 2000);
    ASSERT_STREQ(response->status_message, "OK");
    ASSERT_STREQ(response->client_message_id, "client_message_id");
    FreeSmsSendResponse(response);
    FreeTextSmsSendRequest(request);
    FreeSmsClientContext(context);
  }
}

TEST(CapiTest, SendBinaryMessage) {
  bool ok = true;
  const char* user = GetUsername(&ok);
  const char* pass = GetPassword(&ok);
  if (ok) {
    SmsClientContext* context = CreateSmsClientContext(user, pass, GetUrl());
    Int64Array* addresses = CreateInt64Array(1);
    addresses->array[0] = 1234567;
    uint8_t data[] = { 0x00, 0x01, 0x02 };
    BinaryArray* binary_content = CreateBinaryArray(1);
    binary_content->array[0] = CreateUint8Array(data, 3);
    BinarySmsSendRequest* request  = CreateBinarySmsSendRequest();
    request->message_content = binary_content;
    request->recipient_address_list = addresses;
    request->test = 1;
    request->client_message_id = Strdup("client_message_id");
    int error_code;
    SmsSendResponse* response = SendBinaryMessage(context, request, &error_code);
    ASSERT_EQ(error_code, 0);
    ASSERT_EQ(response->status_code, 2000);
    ASSERT_STREQ(response->status_message, "OK");
    ASSERT_STREQ(response->client_message_id, "client_message_id");
    FreeSmsSendResponse(response);
    FreeBinarySmsSendRequest(request);
    FreeSmsClientContext(context);
  }
}

}  /* namespace */
