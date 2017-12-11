/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include "gtest/gtest.h"

#include <websms/messages.h>
#include <websms/misc.h>

namespace {

using namespace websms;

TEST(MessagesTest, TextMessage) {
  TextMessage message(1234567, "Text message");
  ASSERT_STREQ(message.GetTargetUrl(), "/smsmessaging/text");
  ASSERT_STREQ(message.message_content(), "Text message");
  message.set_message_content("New message");
  ASSERT_STREQ(message.message_content(), "New message");
  ASSERT_EQ(message.recipient_address_list().Size(), 1U);
  ASSERT_EQ(message.recipient_address_list()[0], 1234567);
  ASSERT_EQ(message.max_sms_per_message(), 1);
  message.set_max_sms_per_message(10);
  ASSERT_EQ(message.max_sms_per_message(), 10);
  ASSERT_TRUE(message.test());
  message.set_test(false);
  ASSERT_FALSE(message.test());
  ASSERT_FALSE(message.sender_address());
  message.set_sender_address("sender_address");
  ASSERT_STREQ(message.sender_address(), "sender_address");
  ASSERT_STREQ(message.sender_address_type(), "national");
  message.set_sender_address_type(SenderAddressTypeToString(kInternational));
  ASSERT_STREQ(message.sender_address_type(), "international");
  ASSERT_FALSE(message.send_as_flash_sms());
  message.set_send_as_flash_sms(true);
  ASSERT_TRUE(message.send_as_flash_sms());
  ASSERT_FALSE(message.notification_callback_url());
  message.set_notification_callback_url("notification_callback_url");
  ASSERT_STREQ(message.notification_callback_url(),
               "notification_callback_url");
  ASSERT_FALSE(message.client_message_id());
  message.set_client_message_id("client_message_id");
  ASSERT_STREQ(message.client_message_id(), "client_message_id");
  ASSERT_EQ(message.priority(), 0);
  message.set_priority(1);
  ASSERT_EQ(message.priority(), 1);

  AddressList recipients(1);
  recipients[0] = 1234567;
  TextMessage message2(recipients, "Text message");
  ASSERT_EQ(message2.recipient_address_list().Size(), 1U);
  ASSERT_EQ(message2.recipient_address_list()[0], 1234567);
}

TEST(MessagesTest, BinaryMessage) {
  uint8_t data1[] = { 0x00, 0x01, 0x02 };
  BinaryData binary_content1(1);
  binary_content1.Set(0, data1, 3);
  AddressList recipients(1);
  recipients[0] = 1234567;
  BinaryMessage message(recipients, binary_content1);
  ASSERT_STREQ(message.GetTargetUrl(), "/smsmessaging/binary");
  ASSERT_FALSE(message.user_data_header_present());
  message.set_user_data_header_present(true);
  ASSERT_TRUE(message.user_data_header_present());
  ASSERT_EQ(message.recipient_address_list().Size(), 1U);
  ASSERT_EQ(message.recipient_address_list()[0], 1234567);
  ASSERT_TRUE(message.test());
  message.set_test(false);
  ASSERT_FALSE(message.test());
  ASSERT_FALSE(message.sender_address());
  message.set_sender_address("sender_address");
  ASSERT_STREQ(message.sender_address(), "sender_address");
  ASSERT_STREQ(message.sender_address_type(), "national");
  message.set_sender_address_type(SenderAddressTypeToString(kInternational));
  ASSERT_STREQ(message.sender_address_type(), "international");
  ASSERT_FALSE(message.send_as_flash_sms());
  message.set_send_as_flash_sms(true);
  ASSERT_TRUE(message.send_as_flash_sms());
  ASSERT_FALSE(message.notification_callback_url());
  message.set_notification_callback_url("notification_callback_url");
  ASSERT_STREQ(message.notification_callback_url(),
               "notification_callback_url");
  ASSERT_FALSE(message.client_message_id());
  message.set_client_message_id("client_message_id");
  ASSERT_STREQ(message.client_message_id(), "client_message_id");
  ASSERT_EQ(message.priority(), 0);
  message.set_priority(1);
  ASSERT_EQ(message.priority(), 1);
}

}  /* namespace */
