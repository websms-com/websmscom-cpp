/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#ifndef WEBSMS_HTTP_H_
#define WEBSMS_HTTP_H_

#include <string>

#include <curl/curl.h>

#include <websms/misc.h>

namespace websms {

/**
 * @class HttpRequest
 * @brief Used to send http requests. Uses libcurl, a client-side URL transfer
 * library (http://curl.haxx.se/libcurl/).
 */
class HttpRequest {
 public:
  /// Request has succeeded
  static const int HTTP_OK = 200;
  /// Request requires user authentication
  static const int HTTP_UNAUTHORIZED = 401;

  /**
   * Constructor
   * @param[in] url Target url
   */
  explicit HttpRequest(const std::string& url);
  ~HttpRequest();

  /**
   * Add custom header to request.
   * @param[in] field Field
   * @param[in] value Value
   */
  void AddHeader(std::string field, std::string value);

  /**
   * Send a post request.
   * @param[in] data Data
   * @param[out] response Response
   * @return HTTP response code if positive, else libcurl's result code * -1
   */
  int Post(const std::string& data, std::string* response);

 private:
  static size_t ResponseHandler(char* ptr, size_t size, size_t nmemb,
                                void *userdata);
  std::string url_;
  CURL* handle_;
  curl_slist* headers_;
  DISALLOW_COPY_AND_ASSIGN(HttpRequest)
};

} /* namespace websms */

#endif  /* WEBSMS_HTTP_H_ */
