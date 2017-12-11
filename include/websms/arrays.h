/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 * @file arrays.h
 * @brief Contains array types and wrapper.
 *
 * Also used by the C API.
 */

#ifndef WEBSMS_ARRAY_H_
#define WEBSMS_ARRAY_H_

#include <stdint.h>
#include <stdlib.h>

#include <websms/misc.h>

#ifdef __cplusplus
namespace websms {
#endif

/**
 * @struct Int64Array
 * @brief int64_t-Array
 */
EXTERN_C typedef struct EXPORT Int64Array {
#ifdef __cplusplus
  typedef int64_t DataType;
  static DataType InitialValue() { return 0; }
#endif
  int64_t* array;  ///< Data
  size_t size;  ///< Size
} Int64Array;

/**
 * @struct Uint8Array
 * @brief uint8_t-Array
 */
EXTERN_C typedef struct EXPORT Uint8Array {
#ifdef __cplusplus
  typedef uint8_t DataType;
  static DataType InitialValue() { return 0; }
#endif
  uint8_t* array;  ///< Data
  size_t size;  ///< Size
} Uint8Array;

/**
 * @struct BinaryArray
 * @brief Used to represent binary data.
 */
EXTERN_C typedef struct EXPORT BinaryArray {
#ifdef __cplusplus
  typedef Uint8Array* DataType;
  static DataType InitialValue() { return NULL; }
#endif
  Uint8Array** array;  ///< Data
  size_t size;  ///< Size
} BinaryArray;

#ifdef __cplusplus

/**
 * @class ArrayUtil
 * @brief Array helper functions
 */
class ArrayUtil {
 public:
   /*
   * Create new array.
   * @tparam ArrayType Array type
   * @param[in] size Size
   * @return Array
   */
  template <class ArrayType>
  static ArrayType* Create(size_t size) {
    ArrayType* target = new ArrayType;
    target->size = size;
    if (size > 0) {
      target->array = new typename ArrayType::DataType[size];
      for (size_t i = 0; i < size; i++) {
        target->array[i] = ArrayType::InitialValue();
      }
    } else {
      target->array = NULL;
    }
    return target;
  }

  /**
   * Create new array with copied content of source.
   * @tparam ArrayType Array type
   * @param[in] source Source content
   * @return Array
   */
  template <class ArrayType>
  static ArrayType* Create(const ArrayType* source) {
    ArrayType* target = ArrayUtil::Create<ArrayType>(source ? source->size : 0);
    for (size_t i = 0; i < target->size; ++i) {
      target->array[i] = source->array[i];
    }
    return target;
  }

  /**
   * Create new array with copied content of source.
   * @tparam ArrayType Array type
   * @param[in] source Source content
   * @param[in] size Size of source
   * @return Array
   */
  template <class ArrayType>
  static ArrayType* Create(const typename ArrayType::DataType* source,
                           size_t size) {
    ArrayType* target = ArrayUtil::Create<ArrayType>(size);
    for (size_t i = 0; i < size; ++i) {
      target->array[i] = source[i];
    }
    return target;
  }

  /**
   * Copy Array
   * @tparam ArrayType Array type
   * @param[in] source Source content
   * @return Array
   */
  template <class ArrayType>
  static ArrayType* Copy(const ArrayType* source) {
    return ArrayUtil::Create(source);
  }

  /**
   * Destroys and frees an array.
   * @tparam ArrayType Array type
   * @param[in] source Array
   */
  template <class ArrayType>
  static void Destroy(ArrayType* source) {
    if (source != NULL) {
      if (source->array != NULL && source->size > 0) {
        delete [] source->array;
      }
      delete source;
    }
  }
};

/**
 * @class ArrayWrapper
 * @brief Wrapper for array types.
 * @tparam ArrayType Array type
 */
template <class ArrayType>
class ArrayWrapper {
 public:
  typedef typename ArrayType::DataType DataType;

  /**
   * Constructor
   * @param[in] size Size of internal array
   */
  explicit ArrayWrapper(size_t size)
      : internal_(ArrayUtil::Create<ArrayType>(size)) {
  }

  virtual ~ArrayWrapper() {
    ArrayUtil::Destroy(internal_);
  }

  ArrayWrapper(const ArrayWrapper& source)
      : internal_(ArrayUtil::Copy(source.internal_)) {
  }

  explicit ArrayWrapper(const ArrayType* source)
      : internal_(ArrayUtil::Copy(source)) {
  }

  ArrayWrapper& operator=(const ArrayWrapper& source) {
    ArrayUtil::Destroy(internal_);
    internal_ = ArrayUtil::Copy(source.internal_);
    return *this;
  }

  DataType& operator[] (size_t index) {
    return internal_->array[index];
  }

  const DataType& operator[] (size_t index) const {
    return internal_->array[index];
  }

  /**
   * Return size of internal array.
   * @return
   */
  size_t Size() const {
    return internal_->size;
  }

  /**
   * Return as array (copy).
   * @return
   */
  ArrayType* AsArray() const {
    return ArrayUtil::Copy(internal_);
  }

 protected:
  ArrayType* internal_;
};
#endif

#ifdef __cplusplus
}  // namespace websms
#endif

#endif  /* WEBSMS_ARRAY_H_ */
