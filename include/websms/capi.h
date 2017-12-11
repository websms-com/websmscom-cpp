/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 * @file capi.h
 * @brief The C API.
 */

#ifndef WEBSMS_CAPI_H_
#define WEBSMS_CAPI_H_

#include <stdint.h>

#include <websms/arrays.h>
#include <websms/misc.h>
#include <websms/requests.h>
#include <websms/responses.h>

#ifdef __cplusplus
namespace websms {
#endif

/**
 * @struct SmsClientContext
 * @brief Client context.
 */
EXTERN_C typedef struct EXPORT SmsClientContext {
  const char* username;  ///< User name
  const char* password;  ///< Password
  const char* url;  ///< URL
} SmsClientContext;

/**
 * Creates new client context.
 * @param[in] username User name
 * @param[in] password Password
 * @param[in] url URL
 * @return Client context
 */
EXTERN_C EXPORT SmsClientContext* CreateSmsClientContext(const char* username,
    const char* password, const char* url);

/**
 * Creates new text sms send request.
 * @return Text sms send request
 */
EXTERN_C EXPORT TextSmsSendRequest* CreateTextSmsSendRequest();

/**
 * Creates new binary sms send request.
 * @return Binary sms send request.
 */
EXTERN_C EXPORT BinarySmsSendRequest* CreateBinarySmsSendRequest();

/**
 * Creates new Int64Array
 * @return Array;
 */
EXTERN_C EXPORT Int64Array* CreateInt64Array(size_t size);

/**
 * Creates new Uint8Array
 * @return Array;
 */
EXTERN_C EXPORT Uint8Array* CreateUint8Array(const uint8_t* data, size_t size);

/**
 * Creates new BinaryArray
 * @return Array;
 */
EXTERN_C EXPORT BinaryArray* CreateBinaryArray(size_t size);

/**
 * Frees client context.
 * @param[in] context Client context
 */
EXTERN_C EXPORT void FreeSmsClientContext(SmsClientContext* context);

/**
 * Frees text sms send request.
 * @param[in] request Text sms send request
 */
EXTERN_C EXPORT void FreeTextSmsSendRequest(TextSmsSendRequest* request);

/**
 * Frees binary sms send request.
 * @param[in] request Binary sms send request
 */
EXTERN_C EXPORT void FreeBinarySmsSendRequest(BinarySmsSendRequest* request);

/**
 * Frees sms send response
 * @param[in] response Sms send response
 */
EXTERN_C EXPORT void FreeSmsSendResponse(SmsSendResponse* response);

/**
 * Frees Int64Array
 * @param[in] Array
 */
EXTERN_C EXPORT void FreeInt64Array(Int64Array* array);

/**
 * Frees Uint8Array
 * @param[in] Array
 */
EXTERN_C EXPORT void FreeUint8Array(Uint8Array* array);

/**
 * Frees BinaryArray
 * @param[in] Array
 */
EXTERN_C EXPORT void FreeBinaryArray(BinaryArray* array);

/**
 * Sends text message.
 * @param[in] context Cient context
 * @param[in] request Request
 * @param[out] error_code Error code
 */
EXTERN_C EXPORT SmsSendResponse* SendTextMessage(
    const SmsClientContext* context, const TextSmsSendRequest* request,
    int* error_code);

/**
 * Sends binary message.
 * @param[in] context Cient context
 * @param[in] request Request
 * @param[out] error_code Error code
 */
EXTERN_C EXPORT SmsSendResponse* SendBinaryMessage(
    const SmsClientContext* context, const BinarySmsSendRequest* request,
    int* error_code);

#ifdef __cplusplus
}  /* namespace websms */
#endif

#endif  /* WEBSMS_CAPI_H_ */
