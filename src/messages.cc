/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include <websms/messages.h>

#include <stdint.h>

#include <string>
#include <vector>

#include <websms/arrays.h>
#include <websms/misc.h>
#include <websms/requests.h>

namespace websms {

BinaryData::BinaryData(size_t size)
    : ArrayWrapper(size) {
}

BinaryData::~BinaryData() {
  for (size_t i = 0; i < internal_->size; ++i) {
    delete [] internal_->array[i]->array;
    delete internal_->array[i];
  }
}

void BinaryData::Set(size_t index, const uint8_t* data, size_t size) {
  Uint8Array* prev = (*this)[index];
  Uint8Array* array = ArrayUtil::Create<Uint8Array>(data, size);
  internal_->array[index] = array;
  ArrayUtil::Destroy(prev);
}

TextMessage::TextMessage(const AddressList& recipient_address_list,
                         const char* message_content) {
  set_recipient_address_list(recipient_address_list);
  set_message_content(message_content);
}

TextMessage::TextMessage(int64_t recipient,
                         const char* message_content) {
  dto_->recipient_address_list = ArrayUtil::Create<Int64Array>(1);
  dto_->recipient_address_list->array[0] = recipient;
  set_message_content(message_content);
}

const char* TextMessage::GetTargetUrl() const {
  return TextSmsSendRequest::GetTargetUrl();
}

const char* TextMessage::message_content() const {
  return dto_->message_content;
}

void TextMessage::set_message_content(const char* message_content) {
  Strdel(dto_->message_content);
  dto_->message_content =  Strdup(message_content);
}

int TextMessage::max_sms_per_message() const {
  return dto_->max_sms_per_message;
}

void TextMessage::set_max_sms_per_message(int max_sms_per_message) {
  dto_->max_sms_per_message = max_sms_per_message;
}

bool TextMessage::test() const {
  return dto_->test > 0;
}

void TextMessage::set_test(bool test) {
  dto_->test = test;
}

AddressList TextMessage::recipient_address_list() const {
  return AddressList(dto_->recipient_address_list);
}

void TextMessage::set_recipient_address_list(
    const AddressList& recipient_address_list) {
  ArrayUtil::Destroy(dto_->recipient_address_list);
  dto_->recipient_address_list = recipient_address_list.AsArray();
}

const char* TextMessage::sender_address() const {
  return dto_->sender_address;
}

void TextMessage::set_sender_address(const char* sender_address) {
  Strdel(dto_->sender_address);
  dto_->sender_address =  Strdup(sender_address);
}

const char* TextMessage::sender_address_type() const {
  return dto_->sender_address_type;
}

void TextMessage::set_sender_address_type(
    const char* sender_address_type) {
  Strdel(dto_->sender_address_type);
  dto_->sender_address_type =  Strdup(sender_address_type);
}

bool TextMessage::send_as_flash_sms() const {
  return dto_->send_as_flash_sms > 0;
}

void TextMessage::set_send_as_flash_sms(bool send_as_flash_sms) {
  dto_->send_as_flash_sms = send_as_flash_sms;
}

const char* TextMessage::notification_callback_url() const {
  return dto_->notification_callback_url;
}

void TextMessage::set_notification_callback_url(
    const char* notification_callback_url) {
  Strdel(dto_->notification_callback_url);
  dto_->notification_callback_url =  Strdup(notification_callback_url);
}

const char* TextMessage::client_message_id() const {
  return dto_->client_message_id;
}

void TextMessage::set_client_message_id(const char* client_message_id) {
  Strdel(dto_->client_message_id);
  dto_->client_message_id =  Strdup(client_message_id);
}

int TextMessage::priority() const {
  return dto_->priority;
}

void TextMessage::set_priority(int priority) {
  dto_->priority = priority;
}

BinaryMessage::BinaryMessage(const AddressList& recipient_address_list,
    const BinaryData& message_content) {
  set_recipient_address_list(recipient_address_list);
  set_message_content(message_content);
}

const char* BinaryMessage::GetTargetUrl() const {
  return BinarySmsSendRequest::GetTargetUrl();
}

bool BinaryMessage::user_data_header_present() {
  return dto_->user_data_header_present > 0;
}

void BinaryMessage::set_user_data_header_present(
    bool user_data_header_present) {
  dto_->user_data_header_present =  user_data_header_present;
}

void BinaryMessage::set_message_content(const BinaryData& message_content) {
  if (dto_->message_content != NULL) {
    for (size_t i = 0; i < dto_->message_content->size; ++i) {
      ArrayUtil::Destroy(dto_->message_content->array[i]);
    }
    ArrayUtil::Destroy(dto_->message_content);
  }

  dto_->message_content =
      ArrayUtil::Create<BinaryArray>(message_content.Size());
  if (dto_->message_content != NULL) {
    for (size_t i = 0; i < message_content.Size(); ++i) {
      dto_->message_content->array[i] =
          ArrayUtil::Copy<Uint8Array>(message_content[i]);
    }
  }
}

bool BinaryMessage::test() const {
  return dto_->test > 0;
}

void BinaryMessage::set_test(bool test) {
  dto_->test = test;
}

AddressList BinaryMessage::recipient_address_list() const {
  return AddressList( dto_->recipient_address_list);
}

void BinaryMessage::set_recipient_address_list(
    const AddressList& recipient_address_list) {
  ArrayUtil::Destroy(dto_->recipient_address_list);
  dto_->recipient_address_list = recipient_address_list.AsArray();
}

const char* BinaryMessage::sender_address() const {
  return dto_->sender_address;
}

void BinaryMessage::set_sender_address(const char* sender_address) {
  Strdel(dto_->sender_address);
  dto_->sender_address =  Strdup(sender_address);
}

const char* BinaryMessage::sender_address_type() const {
  return dto_->sender_address_type;
}

void BinaryMessage::set_sender_address_type(
    const char* sender_address_type) {
  Strdel(dto_->sender_address_type);
  dto_->sender_address_type =  Strdup(sender_address_type);
}

bool BinaryMessage::send_as_flash_sms() const {
  return dto_->send_as_flash_sms > 0;
}

void BinaryMessage::set_send_as_flash_sms(bool send_as_flash_sms) {
  dto_->send_as_flash_sms = send_as_flash_sms;
}

const char* BinaryMessage::notification_callback_url() const {
  return dto_->notification_callback_url;
}

void BinaryMessage::set_notification_callback_url(
    const char* notification_callback_url) {
  Strdel(dto_->notification_callback_url);
  dto_->notification_callback_url =  Strdup(notification_callback_url);
}

const char* BinaryMessage::client_message_id() const {
  return dto_->client_message_id;
}

void BinaryMessage::set_client_message_id(
    const char* client_message_id) {
  Strdel(dto_->client_message_id);
  dto_->client_message_id =  Strdup(client_message_id);
}

int BinaryMessage::priority() const {
  return dto_->priority;
}

void BinaryMessage::set_priority(int priority) {
  dto_->priority = priority;
}

const char* MessageResponse::client_message_id() const {
  return dto_->client_message_id;
}

const char*  MessageResponse::transfer_id() const {
  return dto_->transfer_id;
}

int MessageResponse::status_code() const {
  return dto_->status_code;
}

const char* MessageResponse::status_message() const {
  return dto_->status_message;
}

} /* namespace websms */
