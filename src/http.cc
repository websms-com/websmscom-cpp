/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include "http.h"

#include <string>
#include <vector>

#include <curl/curl.h>
#include <jansson.h>

namespace {
class CurlInitialization {
 public:
  CurlInitialization() {
    DBG("%s", "CURL", "global init");
    curl_global_init(CURL_GLOBAL_DEFAULT);
  }
  ~CurlInitialization() {
    DBG("%s", "CURL", "global cleanup");
    curl_global_cleanup();
  }
} init;
}

namespace websms {

HttpRequest::HttpRequest(const std::string& url)
    : url_(url),
      handle_(curl_easy_init()),
      headers_(NULL) {
  DBG("%s", "CURL", url.c_str());
}

HttpRequest::~HttpRequest() {
  if (handle_ != NULL) {
    curl_easy_cleanup(handle_);
  }
  if (headers_ != NULL) {
    curl_slist_free_all(headers_);
  }
}

void HttpRequest::AddHeader(std::string key, std::string value) {
  std::string header = key + ": " + value;
  DBG("%s", "CURL", header.c_str());
  headers_ = curl_slist_append(headers_, header.c_str());
}

int HttpRequest::Post(const std::string& data, std::string* result) {
  curl_easy_reset(handle_);
  curl_easy_setopt(handle_, CURLOPT_URL, url_.c_str());
  curl_easy_setopt(handle_, CURLOPT_WRITEFUNCTION,
                   &HttpRequest::ResponseHandler);
  curl_easy_setopt(handle_, CURLOPT_WRITEDATA, result);
  curl_easy_setopt(handle_, CURLOPT_POSTFIELDS, data.c_str());
  curl_easy_setopt(handle_, CURLOPT_SSL_VERIFYPEER, 0);
  if (headers_ != NULL) {
    curl_easy_setopt(handle_, CURLOPT_HTTPHEADER, headers_);
  }
  curl_easy_setopt(handle_, CURLOPT_USERAGENT, std::string("CPP SDK Client (v" + std::string(Version()) +")").c_str());

  int status = curl_easy_perform(handle_);
  if (status == 0) {
    CURLINFO info;
    curl_easy_getinfo(handle_, CURLINFO_RESPONSE_CODE, &info);
    status = info;
  }
  else {
    status *= (-1);
  }

  DBG("%s", "CURL", data.c_str());
  DBG("status: %d, result: %s", "CURL", status, result->c_str());
  return status;
}

size_t HttpRequest::ResponseHandler(char* ptr, size_t size, size_t nmemb,
                                    void* userdata) {
  std::string* response = static_cast<std::string*>(userdata);
  response->append(ptr, size * nmemb);
  return size * nmemb;
}

}  /* namespace websms */
