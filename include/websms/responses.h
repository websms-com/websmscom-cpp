/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 * @file responses.h
 * @brief Simple data transfer objects representing responses.
 *
 * Also used by the C API.
 */

#ifndef WEBSMS_RESPONSES_H_
#define WEBSMS_RESPONSES_H_

#include <websms/misc.h>

#ifdef __cplusplus
namespace websms {
#endif

/**
 * @struct SmsSendResponse
 * @brief Represents a response to a SMS send request.
 * @see MessageResponse
 */
EXTERN_C typedef struct EXPORT SmsSendResponse {
  const char* client_message_id;  ///< User-defined message id
  const char* transfer_id;  ///< Transfer id
  int status_code;  ///< Status code
  const char* status_message;  ///< Detailed status information
#ifdef __cplusplus
  /**
   * Create and initialize object.
   * @return Object
   */
  static SmsSendResponse* Create();

  /**
   * Create a copy of an object.
   * @return Object
   */
  static SmsSendResponse* Copy(SmsSendResponse* dto);

  /**
   * Destroys object and frees memory.
   * @param[in] dto
   */
  static void Destroy(SmsSendResponse* dto);

  /**
   * Serialize object.
   * @param[in] dto Object
   * @return Serialized object
   */
  static const char* Serialize(const SmsSendResponse* dto);

  /**
   * Deserialize input string and store the result in the target object.
   * @param[in] data Serialized string
   * @param[out] dto Target object
   * @return True on success
   */
  static bool Deserialize(const char* data, SmsSendResponse* dto);
#endif
} SmsSendResponse;

#ifdef __cplusplus
}  /* namespace websms */
#endif

#endif  /* WEBSMS_RESPONSES_H_ */
