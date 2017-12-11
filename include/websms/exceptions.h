/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 * @file exceptions.h
 * @brief Contains all available exceptions.
 */

#ifndef WEBSMS_EXCEPTIONS_H_
#define WEBSMS_EXCEPTIONS_H_

#include <websms/misc.h>

namespace websms {

/**
 * @class Exception
 * @brief Base class of all exceptions.
 */
class EXPORT Exception {
 public:
  /**
   * Constructor
   * @param[in] message Error message
   */
  explicit Exception(const char* message);

  /**
   * Constructor
   * @param[in] message Error message
   * @param[in] error_code Error code
   */
  Exception(const char* message, int error_code);
  explicit Exception(const Exception& source);
  virtual ~Exception();

  Exception& operator=(const Exception& source);

  /**
   * Returns error description
   * @return Error description
   */
  virtual const char* What() const;

  /**
   * Returns error code
   * @return Error code
   */
  int error_code() const;

  /**
   * Returns error message
   * @return Error message
   */
  const char* message() const;

 private:
  const char* message_;
  int error_code_;
};

/**
 * @class ApiException
 * @brief Signals API errors. For details check status_code.
 * @see StatusCode
 */
class EXPORT ApiException : public Exception {
 public:
  /**
   * Constructor
   * @param[in] status_message Status message
   * @param[in] status_code Status code
   */
  ApiException(const char* status_message, int status_code);

  /**
   * Returns status code
   * @return status code
   */
  int status_code() const;

  /**
   * Returns status message
   * @return status message
   */
  const char* status_message() const;
};

/**
 * @class AuthorizationFailedException
 * @brief Invalid user and/or password.
 */
class EXPORT AuthorizationFailedException: public Exception {
 public:
  /**
   * Constructor
   * @param[in] message Error message
   */
  explicit AuthorizationFailedException(const char* message);
};

/**
 * @class HttpConnectionException
 * @brief Signals HTTP error.
 */
class EXPORT HttpConnectionException: public Exception {
 public:
  /**
   * Constructor
   * @param[in] message Error message
   * @param[in] error_code Error code
   */
  HttpConnectionException(const char* message, int error_code);
};

/**
 * @class ParameterValidationException
 * @brief Signals invalid or missing parameters.
 */
class EXPORT ParameterValidationException: public Exception {
 public:
  /**
   * Constructor
   * @param[in] message Error message
   */
  explicit ParameterValidationException(const char* message);
};

}  /* namespace websms */

#endif  /* WEBSMS_EXCEPTIONS_H_ */
