/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 * @file requests.h
 * @brief Simple data transfer objects representing requests.
 *
 * Also used by the C API.
 */

#ifndef WEBSMS_REQUESTS_H_
#define WEBSMS_REQUESTS_H_

#include <stdint.h>

#include <websms/arrays.h>
#include <websms/misc.h>

#ifdef __cplusplus
namespace websms {
#endif

/**
 * @struct TextSmsSendRequest
 * @brief Represents a text sms send request.
 * @see TextMessage
 */
EXTERN_C typedef struct EXPORT TextSmsSendRequest {
  const char* message_content;  ///< Message content
  int max_sms_per_message;  ///< Set max number of messages to be send
  int test;  ///< Test message?
  Int64Array* recipient_address_list;  ///< List of recipients
  const char* sender_address;  ///< Address of sender
  const char* sender_address_type;  ///< Type of sender address
  int send_as_flash_sms;  ///< Send as flash sms?
  const char* notification_callback_url;  ///< Notification url
  const char* client_message_id;  ///< User-defined message id
  uint32_t priority;  ///< Priority
  const char* auth_token;  ///< Authentification information
  const char* api_key;
#ifdef __cplusplus
  /**
   * Create and initialize object.
   * @return Object
   */
  static TextSmsSendRequest* Create();

  /**
   * Create a copy of an object.
   * @return Object
   */
  static TextSmsSendRequest* Copy(TextSmsSendRequest* dto);

  /**
   * Destroys object and frees memory.
   * @param[in] dto
   */
  static void Destroy(TextSmsSendRequest* dto);

  /**
   * Serialize object.
   * @param[in] dto Object
   * @return Serialized object
   */
  static const char* Serialize(const TextSmsSendRequest* dto);

  /**
   * Deserialize input string and store the result in the target object.
   * @param[in] data Serialized string
   * @param[out] dto Target object
   * @return True on success
   */
  static bool Deserialize(const char* data, TextSmsSendRequest* dto);
  static const char* GetTargetUrl() { return "/smsmessaging/text"; }
#endif
} TextSmsSendRequest;

/**
 * @struct BinarySmsSendRequest
 * @brief Represents a binary sms send request.
 * @see BinaryMessage
 */
EXTERN_C typedef struct EXPORT BinarySmsSendRequest {
  int user_data_header_present;
  BinaryArray* message_content;  ///< Message content
  int test;  ///< Test message?
  Int64Array* recipient_address_list;  ///< List of recipients
  const char* sender_address;  ///< Address of sender
  const char* sender_address_type;  ///< Type of sender address
  int send_as_flash_sms;  ///< Send as flash sms?
  const char* notification_callback_url;  ///< Notification url
  const char* client_message_id;  ///< User-defined message id
  uint32_t priority;  ///< Priority
  const char* auth_token;  ///< Authentification information
  const char* api_key;
#ifdef __cplusplus
  /**
   * Create and initialize object.
   * @return Object
   */
  static BinarySmsSendRequest* Create();

  /**
   * Create a copy of an object.
   * @return Object
   */
  static BinarySmsSendRequest* Copy(BinarySmsSendRequest* dto);

  /**
   * Destroys object and frees memory.
   * @param[in] dto
   */
  static void Destroy(BinarySmsSendRequest* dto);

  /**
   * Serialize object.
   * @param[in] dto Object
   * @return Serialized object
   */
  static const char* Serialize(const BinarySmsSendRequest* dto);

  /**
   * Deserialize input string and store the result in the target object.
   * @param[in] data Serialized string
   * @param[out] dto Target object
   * @return True on success
   */
  static bool Deserialize(const char* data, BinarySmsSendRequest* dto);
  static const char* GetTargetUrl() { return "/smsmessaging/binary"; }
#endif
} BinarySmsSendRequest;

#ifdef __cplusplus
}  /* namespace websms */
#endif

#endif  /* WEBSMS_REQUESTS_H_ */
