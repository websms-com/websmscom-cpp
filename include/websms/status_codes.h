/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 * @file status_code.h
 * @brief Provides enum with all possible status codes.
 *
 * Also used by the C API.
 */
#ifndef WEBSMS_STATUS_CODES_H_
#define WEBSMS_STATUS_CODES_H_

#ifdef __cplusplus
namespace websms {
#endif

/**
 * @enum StatusCode
 * @brief All status codes that can be returned by requests.
 */
typedef enum StatusCode {
  /// Message sent
  kOk = 2000,
  /// Message queued
  kOkQueued = 2001,
  /// Test ok
  kOkTest = 2002,
  /// Malformed XML/JSON
  kMalformedXml = 4000,
  /// Invalid credentials
  kInvalidCredentials = 4001,
  /// At least one recipient address is invalid
  kInvalidRecipient = 4002,
  /// Invalid sender
  kInvalidSender = 4003,
  /// Invalid message type
  kInvalidMessageType = 4004,
  /// Invalid message alphabet
  kInvalidMessageAlphabet = 4005,
  /// Invalid message class
  kInvalidMessageClass = 4006,
  /// Invalid message data
  kInvalidMessageData = 4007,
  /// Invalid message id
  kInvalidMessageId = 4008,
  /// Invalid text
  kInvalidText = 4009,
  /// Invalid autosegment
  kInvalidAutosegment = 4010,
  /// Invalid COD
  kInvalidCod = 4011,
  /// Throttling. Allowed message rate exceeded.
  kThrottling = 4012,
  /// The allowed message limit exceeded.
  kMsgLimitExceeded = 4013,
  /// Unauthorized IP
  kUnauthorizedIp = 4014,
  /// Invalid priority
  kInvalidMessagePriority = 4015,
  /// Invalid COD return address
  kInvalidCodReturnaddress = 4016,
  /// Message would generate multiple segments, but option is not enabled.
  kMultisegments = 4017,
  /// Method not allowed
  kApiMethodForbidden = 4018,
  /// Parameter missing
  kParameterMissing = 4019,
  /// Invalid API key
  kInvalidApiKey = 4020,
  /// Invalid auth token
  kInvalidAuthToken = 4021,
  /// Access denied
  kAccessDenied = 4022,
  /// Rate Limit Exceeded, spam check
  kThrottlingSpamming_ip = 4023,
  /// Too many requests
  kThrottlingTooManyRequests = 4024,
  /// Too many recipients
  kThrottlingTooManyRecipients = 4025,
  /// Message content too long
  kMaxSmsPerMessageExceeded = 4026,
  /// Internal error
  kInternalError = 5000,
  /// Service not available
  kServiceUnavailable = 5003
} StatusCode;

#ifdef __cplusplus
}  /* namespace websms */
#endif

#endif  /* WEBSMS_STATUS_CODES_H_ */
