/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include <websms/responses.h>
#include <websms/misc.h>
#include <websms/status_codes.h>

#include "json.h"

namespace websms {

SmsSendResponse* SmsSendResponse::Create() {
  SmsSendResponse* dto = new SmsSendResponse();
  dto->client_message_id = NULL;
  dto->transfer_id = NULL;
  StatusCode code = kOk;
  dto->status_code = static_cast<int>(code);
  dto->status_message = NULL;
  return dto;
}

SmsSendResponse* SmsSendResponse::Copy(SmsSendResponse* dto) {
  SmsSendResponse* copy = new SmsSendResponse();
  copy->client_message_id = Strdup(dto->client_message_id);
  copy->transfer_id = Strdup(dto->transfer_id);
  copy->status_code = dto->status_code;
  copy->status_message = Strdup(dto->status_message);
  return copy;
}

void SmsSendResponse::Destroy(SmsSendResponse* dto) {
  if (!dto) {
    return;
  }
  Strdel(dto->client_message_id);
  Strdel(dto->transfer_id);
  Strdel(dto->status_message);
  delete dto;
}

const char* SmsSendResponse::Serialize(const SmsSendResponse* dto) {
  Json json;
  json.Add("clientMessageId", dto->client_message_id);
  json.Add("transferId", dto->transfer_id);
  json.Add("statusCode", dto->status_code);
  json.Add("statusMessage", dto->status_message);
  return Strdup(json.GetAsString().c_str());
}

bool SmsSendResponse::Deserialize(const char* data, SmsSendResponse* dto) {
  Json json;
  if (json.Parse(data)) {
    json.Get("clientMessageId", &dto->client_message_id);
    json.Get("transferId", &dto->transfer_id);
    json.Get("statusCode", &dto->status_code);
    json.Get("statusMessage", &dto->status_message);
    return true;
  }
  return false;
}

} /* namespace websms */
