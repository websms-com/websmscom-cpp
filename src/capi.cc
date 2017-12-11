/**
 * Copyright (c) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include <stdint.h>

#include <websms/capi.h>
#include <websms/misc.h>
#include <websms/requests.h>
#include <websms/status_codes.h>

#include "base64.h"
#include "http.h"

#include <iostream>

namespace websms {

SmsClientContext* CreateSmsClientContext(const char* username,
    const char* password, const char* url) {
  SmsClientContext* context = new SmsClientContext();
  context->username = Strdup(username);
  context->password = Strdup(password);
  context->url = Strdup(url);
  return context;
}

TextSmsSendRequest* CreateTextSmsSendRequest() {
  return TextSmsSendRequest::Create();
}

BinarySmsSendRequest* CreateBinarySmsSendRequest() {
  return BinarySmsSendRequest::Create();
}

Int64Array* CreateInt64Array(size_t size) {
  return ArrayUtil::Create<Int64Array>(size);
}

Uint8Array* CreateUint8Array(const uint8_t* data, size_t size) {
  return ArrayUtil::Create<Uint8Array>(data, size);
}

BinaryArray* CreateBinaryArray(size_t size) {
  return ArrayUtil::Create<BinaryArray>(size);
}

void FreeSmsClientContext(SmsClientContext* context) {
  delete [] context->username;
  delete [] context->password;
  delete [] context->url;
  delete context;
}

void FreeTextSmsSendRequest(TextSmsSendRequest* request) {
  TextSmsSendRequest::Destroy(request);
}

void FreeBinarySmsSendRequest(BinarySmsSendRequest* request) {
  BinarySmsSendRequest::Destroy(request);
}

void FreeSmsSendResponse(SmsSendResponse* response) {
  SmsSendResponse::Destroy(response);
}

void FreeInt64Array(Int64Array* array) {
  ArrayUtil::Destroy(array);
}

void FreeUint8Array(Uint8Array* array) {
  ArrayUtil::Destroy(array);
}

void FreeBinaryArray(BinaryArray* array) {
  ArrayUtil::Destroy(array);
}

SmsSendResponse* SendRequest(const SmsClientContext* context,
                             const char* target_url,
                             const char* data, int* error_code) {
  std::string url(context->url);
  url.append(target_url);
  HttpRequest http(url);
  http.AddHeader("Content-Type", "application/json");
  std::string auth(context->username);
  auth.append(":");
  auth.append(context->password);
  http.AddHeader("Authorization", std::string("Basic ")
      + Base64::Encode<std::string>(auth));
  std::string response;
  int status = http.Post(std::string(data), &response);
  SmsSendResponse* rtn = NULL;
  if (status == HttpRequest::HTTP_OK) {
    rtn = SmsSendResponse::Create();
    SmsSendResponse::Deserialize(response.c_str(), rtn);
    StatusCode code = static_cast<StatusCode>(rtn->status_code);
    switch (code) {
      case kOk:
      case kOkQueued:
      case kOkTest: {
        *error_code = 0;
        break;
      }
      default: {
        *error_code = rtn->status_code;
        break;
      }
    }
  } else {
    *error_code = status;
  }
  return rtn;
}

SmsSendResponse* SendTextMessage(const SmsClientContext* context,
                                 const TextSmsSendRequest* request,
                                 int* error_code) {
  const char* serialized = TextSmsSendRequest::Serialize(request);
  SmsSendResponse* rtn = SendRequest(context,
      TextSmsSendRequest::GetTargetUrl(), serialized, error_code);
  delete [] serialized;
  return rtn;
}

SmsSendResponse* SendBinaryMessage(const SmsClientContext* context,
                                   const BinarySmsSendRequest* request,
                                   int* error_code) {
  const char* serialized = BinarySmsSendRequest::Serialize(request);
  SmsSendResponse* rtn = SendRequest(context,
      BinarySmsSendRequest::GetTargetUrl(), serialized, error_code);
  delete [] serialized;
  return rtn;
}

}  /* namespace websms */
