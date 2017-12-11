/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include <websms/exceptions.h>
#include <websms/misc.h>

namespace websms {

Exception::Exception(const char* message)
    : message_(Strdup(message)),
      error_code_(0) {
}

Exception::Exception(const char* message, int error_code)
    : message_(Strdup(message)),
      error_code_(error_code) {
}

Exception::Exception(const Exception& source)
    : message_(Strdup(source.message_)),
      error_code_(source.error_code_) {
}

Exception::~Exception() {
  Strdel(message_);
}

Exception& Exception::operator=(const Exception& source) {
  Strdel(message_);
  message_ = Strdup(source.message_);
  error_code_ = source.error_code_;
  return *this;
}

const char* Exception::What() const {
  return message_;
}

int Exception::error_code() const {
  return error_code_;
}

const char* Exception::message() const {
  return message_;
}

ApiException::ApiException(const char* status_message, int status_code)
    : Exception(status_message, status_code) {
}


int ApiException::status_code() const {
  return error_code();
}

const char* ApiException::status_message() const {
  return message();
}

AuthorizationFailedException::AuthorizationFailedException(const char* message)
    : Exception(message) {
}

HttpConnectionException::HttpConnectionException(const char* message,
                                                 int error_code)
    : Exception(message, error_code) {
}

ParameterValidationException::ParameterValidationException(const char* message)
    : Exception(message) {
}

}  /* namespace websms */
