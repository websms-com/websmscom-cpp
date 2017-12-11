/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

// TODO(markus): Add some alternate sending methods
#ifndef WEBSMS_SMS_CLIENT_H_
#define WEBSMS_SMS_CLIENT_H_

#include <websms/exceptions.h>
#include <websms/messages.h>
#include <websms/misc.h>

namespace websms {

/**
 * @class SmsClient
 * @brief Containts methods for sending SMS messages.
 */
class EXPORT SmsClient {
 public:
  /**
   * Constructor
   * @param[in] username User name
   * @param[in] password Password
   * @param[in] url URL
   */
  SmsClient(const char* username, const char* password, const char* url);
  ~SmsClient();

  /**
   * Sends text message.
   * @param[in] message Text message
   * @param[in] max_sms_per_message Max sms per message
   * @param[in] test Test flag
   * @throw ApiException
   * @throw AuthorizationFailedException
   * @throw HttpConnectionException
   * @throw ParameterValidationException
   * @return Response
   */
  MessageResponse Send(TextMessage message, int max_sms_per_message, bool test);

  /**
   * Sends binary message.
   * @param[in] message Binary message
   * @param[in] test Test flag
   * @throw ApiException
   * @throw AuthorizationFailedException
   * @throw HttpConnectionException
   * @throw ParameterValidationException
   * @return Response
   */
  MessageResponse Send(BinaryMessage message, bool test);

 private:
  const char* username_;
  const char* password_;
  const char* url_;

  /**
   * Sends message request.
   * @param[in] request
   * @return Response
   */
  template<class T>
  MessageResponse Send(Request<T>* request);
  DISALLOW_COPY_AND_ASSIGN(SmsClient)
};

}  /* namespace websms */

#endif /* WEBSMS_SMS_CLIENT_H_ */
