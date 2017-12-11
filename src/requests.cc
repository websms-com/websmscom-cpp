/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include <stdint.h>

#include <websms/arrays.h>
#include <websms/requests.h>
#include <websms/misc.h>

#include "base64.h"
#include "json.h"

namespace websms {

TextSmsSendRequest* TextSmsSendRequest::Create() {
  TextSmsSendRequest* dto = new TextSmsSendRequest();
  dto->message_content = NULL;
  dto->max_sms_per_message = 1;
  dto->test = true;
  dto->recipient_address_list = NULL;
  dto->sender_address = NULL;
  dto->sender_address_type = Strdup(SenderAddressTypeToString(kNational));
  dto->send_as_flash_sms = false;
  dto->notification_callback_url = NULL;
  dto->client_message_id = NULL;
  dto->priority = 0;
  dto->auth_token = NULL;
  dto->api_key = NULL;
  return dto;
}

TextSmsSendRequest* TextSmsSendRequest::Copy(TextSmsSendRequest* dto) {
  TextSmsSendRequest* copy = new TextSmsSendRequest();
  copy->message_content = Strdup(dto->message_content);
  copy->max_sms_per_message = dto->max_sms_per_message;
  copy->test = dto->test;
  copy->recipient_address_list = ArrayUtil::Copy(dto->recipient_address_list);
  copy->sender_address = Strdup(dto->sender_address);
  copy->sender_address_type = Strdup(dto->sender_address_type);
  copy->send_as_flash_sms = dto->send_as_flash_sms;
  copy->notification_callback_url =Strdup(dto->notification_callback_url);
  copy->client_message_id = Strdup(dto->client_message_id);
  copy->priority = dto->priority;
  copy->auth_token = Strdup(dto->auth_token);
  copy->api_key = Strdup(dto->api_key);
  return copy;
}

void TextSmsSendRequest::Destroy(TextSmsSendRequest* dto) {
  if (!dto) {
    return;
  }
  Strdel(dto->message_content);
  ArrayUtil::Destroy(dto->recipient_address_list);
  Strdel(dto->sender_address);
  Strdel(dto->sender_address_type);
  Strdel(dto->notification_callback_url);
  Strdel(dto->client_message_id);
  Strdel(dto->auth_token);
  Strdel(dto->api_key);
  delete dto;
}

const char* TextSmsSendRequest::Serialize(const TextSmsSendRequest* dto) {
  Json json;
  json.Add("messageContent", dto->message_content);
  json.Add("maxSmsPerMessage", dto->max_sms_per_message);
  json.Add("test", dto->test > 0);
  std::vector<int64_t> v(dto->recipient_address_list->array,
      dto->recipient_address_list->array + dto->recipient_address_list->size);
  json.Add("recipientAddressList", v);
  json.Add("senderAddress", dto->sender_address);
  json.Add("senderAddressType", dto->sender_address_type);
  json.Add("sendAsFlashSms", dto->send_as_flash_sms > 0);
  json.Add("notificationCallbackUrl", dto->notification_callback_url);
  json.Add("clientMessageId", dto->client_message_id);
  json.Add("priority", dto->priority);
  json.Add("authToken", dto->auth_token);
  json.Add("apiKey", dto->api_key);
  return Strdup(json.GetAsString().c_str());
}

bool TextSmsSendRequest::Deserialize(const char*, TextSmsSendRequest*) {
  return false;
}

BinarySmsSendRequest* BinarySmsSendRequest::Create() {
  BinarySmsSendRequest* dto = new BinarySmsSendRequest();
  dto->user_data_header_present = 0;
  dto->message_content = NULL;
  dto->test = true;
  dto->recipient_address_list = NULL;
  dto->sender_address = NULL;
  dto->sender_address_type = Strdup(SenderAddressTypeToString(kNational));
  dto->send_as_flash_sms = false;
  dto->notification_callback_url = NULL;
  dto->client_message_id = NULL;
  dto->priority = 0;
  dto->auth_token = NULL;
  dto->api_key = NULL;
  return dto;
}

BinarySmsSendRequest* BinarySmsSendRequest::Copy(BinarySmsSendRequest* dto) {
  BinarySmsSendRequest* copy = new BinarySmsSendRequest();
  copy->user_data_header_present = dto->user_data_header_present;
  copy->message_content = ArrayUtil::Create<BinaryArray>(
      dto->message_content->size);
  if (copy->message_content != NULL) {
    for (size_t i = 0; i < copy->message_content->size; ++i) {
      copy->message_content->array[i] = ArrayUtil::Copy(
          dto->message_content->array[i]);
    }
  }
  copy->test = dto->test;
  copy->recipient_address_list = ArrayUtil::Copy(dto->recipient_address_list);
  copy->sender_address = Strdup(dto->sender_address);
  copy->sender_address_type = Strdup(dto->sender_address_type);
  copy->send_as_flash_sms = dto->send_as_flash_sms;
  copy->notification_callback_url =Strdup(dto->notification_callback_url);
  copy->client_message_id = Strdup(dto->client_message_id);
  copy->priority = dto->priority;
  copy->auth_token = Strdup(dto->auth_token);
  copy->api_key = Strdup(dto->api_key);
  return copy;
}

void BinarySmsSendRequest::Destroy(BinarySmsSendRequest* dto) {
  if (!dto) {
    return;
  }
  if (dto->message_content != NULL) {
    for (size_t i = 0; i < dto->message_content->size; ++i) {
      ArrayUtil::Destroy(dto->message_content->array[i]);
    }
    ArrayUtil::Destroy(dto->message_content);
  }
  ArrayUtil::Destroy(dto->recipient_address_list);
  Strdel(dto->sender_address);
  Strdel(dto->sender_address_type);
  Strdel(dto->notification_callback_url);
  Strdel(dto->client_message_id);
  Strdel(dto->auth_token);
  Strdel(dto->api_key);
  delete dto;
}

const char* BinarySmsSendRequest::Serialize(const BinarySmsSendRequest* dto) {
  Json json;
  json.Add("userDataHeaderPresent", dto->user_data_header_present > 0);
  std::vector<std::string> content;
  if (dto->message_content != NULL) {
    for (size_t i = 0; i < dto->message_content->size; ++i) {
      std::vector<uint8_t> v(dto->message_content->array[i]->array,
          dto->message_content->array[i]->array
          + dto->message_content->array[i]->size);
      std::string encoded = Base64::Encode<std::vector<uint8_t> >(v);
      content.push_back(encoded);
    }
  }
  json.Add("messageContent", content);
  json.Add("test", dto->test > 0);
  std::vector<int64_t> v(dto->recipient_address_list->array,
      dto->recipient_address_list->array + dto->recipient_address_list->size);
  json.Add("recipientAddressList", v);
  json.Add("senderAddress", dto->sender_address);
  json.Add("senderAddressType", dto->sender_address_type);
  json.Add("sendAsFlashSms", dto->send_as_flash_sms > 0);
  json.Add("notificationCallbackUrl", dto->notification_callback_url);
  json.Add("clientMessageId", dto->client_message_id);
  json.Add("priority", dto->priority);
  json.Add("authToken", dto->auth_token);
  json.Add("apiKey", dto->api_key);
  return Strdup(json.GetAsString().c_str());
}

bool BinarySmsSendRequest::Deserialize(const char*, BinarySmsSendRequest*) {
  return false;
}

} /* namespace websms */
