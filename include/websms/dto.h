/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 * @file serialization.h
 * @brief Contains wrapper template class for data transfer objects.
 */

#ifndef WEBSMS_DTO_H_
#define WEBSMS_DTO_H_

namespace websms {

/**
 * @class DtoWrapper
 * @brief Base class for data transfer object wrappers.
 * @see DtoSupport
 *
 * Handles creation, destruction and deserialization of the embedded data
 * transfer object.
 */
template<class T>
class DtoWrapper {
 public:
  /**
   * Constructor
   * @brief Creates internal object.
   */
  DtoWrapper()
      : dto_(T::Create()) {
  }

  /**
   * Destructor
   * @brief Destroys internal object
   */
  virtual ~DtoWrapper() {
    T::Destroy(dto_);
  }

  DtoWrapper(const DtoWrapper& source)
      : dto_(T::Copy(source.dto_)) {
  }

  /**
   * Assignment operator
   * @param[in] source Source
   */
  DtoWrapper& operator=(const DtoWrapper& source) {
    T::Destroy(dto_);
    dto_ = T::Copy(source.dto_);
    return *this;
  }

  /**
   * Serialize internal object.
   * @return Serialized object
   */
  const char* Serialize() const {
    return T::Serialize(dto_);
  }

  /**
   * Deserialize input string and store result in internal object.
   * @param[in] data Serialized string
   * @return True on success
   */
  bool Deserialize(const char* data) {
    return T::Deserialize(data, dto_);
  }

 protected:
  T* dto_;
};

} /* namespace websms */

#endif  /* WEBSMS_DTO_H_ */
