/**
 * Copyright (c) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 * @file messages.h
 * @brief Classes for C++ API.
 */

#ifndef WEBSMS_MESSAGES_H_
#define WEBSMS_MESSAGES_H_

#include <stdint.h>

#include <websms/arrays.h>
#include <websms/dto.h>
#include <websms/misc.h>
#include <websms/requests.h>
#include <websms/responses.h>

namespace websms {

/**
 * @typedef AddressList
 * @brief Represents address list.
 */
typedef ArrayWrapper<Int64Array> AddressList;

/**
 * @typedef ByteArray
 * @brief Represents byte array;
 */
typedef ArrayWrapper<Uint8Array> ByteArray;

/**
 * @class BinaryData
 * @brief Represents binary data.
 */
class EXPORT BinaryData : public ArrayWrapper<BinaryArray> {
 public:
  /**
   * Constructor
   * @param[in] size Size of internal array
   */
  explicit BinaryData(size_t size);
  ~BinaryData();
  /**
   * Sets data at index
   * @param[in] index Index
   * @param[in] data Binary data
   * @param[in] size Size of data
   */
  void Set(size_t index, const uint8_t* data, size_t size);
};

/**
 * @class Request
 * @brief Base class for requests.
 */
template<class T>
class Request : public DtoWrapper<T> {
 public:
  /**
   * Return target url (relative).
   * @return Target url
   */
  virtual const char* GetTargetUrl() const = 0;
};

/**
 * @class Response
 * @brief Base class for responses.
 */
template<class T>
class Response : public DtoWrapper<T> {
};

/**
 * @class TextMessage
 * @brief Used to send a text sms message.
 * @see TextSmsSendRequest
 */
class EXPORT TextMessage : public Request<TextSmsSendRequest> {
 public:
  /**
   * Constructor
   * @param[in] recipient_address_list List of recipients
   * @param[in] message_content Message content
   */
  TextMessage(const AddressList& recipient_address_list,
              const char* message_content);

  /**
   * Constructor
   * @param[in] recipient Single recipient
   * @param[in] message_content Message content
   */
  TextMessage(int64_t recipient, const char* message_content);
  TextMessage() {}
  virtual const char* GetTargetUrl() const;
  const char* message_content() const;
  void set_message_content(const char* message_content);
  int max_sms_per_message() const;
  void set_max_sms_per_message(int max_sms_per_message);
  bool test() const;
  void set_test(bool test);
  AddressList recipient_address_list() const;
  void set_recipient_address_list(const AddressList& recipient_address_list);
  const char* sender_address() const;
  void set_sender_address(const char* sender_address);
  const char* sender_address_type() const;
  void set_sender_address_type(const char* sender_address_type);
  bool send_as_flash_sms() const;
  void set_send_as_flash_sms(bool send_as_flash_sms);
  const char* notification_callback_url() const;
  void set_notification_callback_url(const char* notification_callback_url);
  const char* client_message_id() const;
  void set_client_message_id(const char* client_message_id);
  int priority() const;
  void set_priority(int priority);
};

/**
 * @class BinaryMessage
 * @brief Used to send a binary sms message
 * @see BinarySmsSendRequest
 */
class EXPORT BinaryMessage : public Request<BinarySmsSendRequest> {
 public:
  /**
   * Constructor
   * @param[in] recipient_address_list List of recipients
   * @param[in] message_content Binary message content
   * @see BinarySmsSendRequest
   */
  BinaryMessage(const AddressList& recipient_address_list,
                const BinaryData& message_content);
  BinaryMessage() {}
  virtual const char* GetTargetUrl() const;
  bool user_data_header_present();
  void set_user_data_header_present(bool user_data_header_present);
  // BinaryData message_content() const; TODO(markus) Provide implementation
  void set_message_content(const BinaryData& message_content);
  bool test() const;
  void set_test(bool test);
  AddressList recipient_address_list() const;
  void set_recipient_address_list(const AddressList& recipient_address_list);
  const char* sender_address() const;
  void set_sender_address(const char* sender_address);
  const char* sender_address_type() const;
  void set_sender_address_type(const char* sender_address_type);
  bool send_as_flash_sms() const;
  void set_send_as_flash_sms(bool send_as_flash_sms);
  const char* notification_callback_url() const;
  void set_notification_callback_url(const char* notification_callback_url);
  const char* client_message_id() const;
  void set_client_message_id(const char* client_message_id);
  int priority() const;
  void set_priority(int priority);
};

/**
 * @class MessageResponse
 * @brief Response to message send request.
 * @see SmsSendResponse
 */
class EXPORT MessageResponse : public Response<SmsSendResponse> {
 public:
  const char* client_message_id() const;
  const char* transfer_id() const;
  int status_code() const;
  const char* status_message() const;
};

} /* namespace websms */

#endif /* WEBSMS_MESSAGES_H_ */
