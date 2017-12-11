/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include <websms/sms_client.h>

#include <websms/exceptions.h>
#include <websms/messages.h>
#include <websms/misc.h>
#include <websms/status_codes.h>

#include "base64.h"
#include "http.h"

namespace websms {

SmsClient::SmsClient(const char* username, const char* password,
                     const char* url)
    : username_(Strdup(username)),
      password_(Strdup(password)),
      url_(Strdup(url)) {
}

SmsClient::~SmsClient() {
  Strdel(username_);
  Strdel(password_);
  Strdel(url_);
}

MessageResponse SmsClient::Send(TextMessage message, int max_sms_per_message,
                                bool test) {
  message.set_max_sms_per_message(max_sms_per_message);
  message.set_test(test);
  return Send(&message);
}

MessageResponse SmsClient::Send(BinaryMessage message, bool test) {
  message.set_test(test);
  return Send(&message);
}

template<class T>
MessageResponse SmsClient::Send(Request<T>* request) {
  std::string url(url_);
  url.append(request->GetTargetUrl());
  HttpRequest http(url);
  http.AddHeader("Content-Type", "application/json");
  std::string auth(username_);
  auth.append(":");
  auth.append(password_);
  http.AddHeader("Authorization", std::string("Basic ")
      + Base64::Encode<std::string>(auth));
  std::string response;
  const char* serialized = request->Serialize();
  int status = http.Post(std::string(serialized), &response);
  delete [] serialized;
  if (status == HttpRequest::HTTP_UNAUTHORIZED) {
    throw AuthorizationFailedException("Authorization failed.");
  }
  else if (status != HttpRequest::HTTP_OK) {
    throw HttpConnectionException("HTTP request failed.", status);
  }
  MessageResponse rtn;
  rtn.Deserialize(response.c_str());
  StatusCode code = static_cast<StatusCode>(rtn.status_code());
  switch (code) {
    case kOk:
    case kOkQueued:
    case kOkTest: {
      break;
    }
    default: {
      throw ApiException(rtn.status_message(), rtn.status_code());
    }
  }
  return rtn;
}

}
