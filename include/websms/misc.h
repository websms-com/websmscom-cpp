/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 * @file misc.h
 * @brief Contains miscellaneous structs, classes and macros.
 *
 * Also used by the C API.
 */

#ifndef WEBSMS_MISC_H_
#define WEBSMS_MISC_H_

/**
 * @def DISALLOW_COPY_AND_ASSIGN
 * @brief Disallows copying and assignment
 */
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&);

#ifdef DEBUG
/**
 * @def DBG
 * @brief Prints debug message, if DEBUG defined.
 */
#define DBG(Format, Category, ...) \
  fprintf(stderr, "[%s] "Format" (%s)\n", \
          (Category), __VA_ARGS__ , __FUNCTION__)
#else
#define DBG(Format, Category, ...)
#endif

#ifdef _WIN32
/**
 * @def EXPORT
 * @brief DLL-Export for Windows
 */
#define EXPORT __declspec(dllexport)
#ifdef __cplusplus
/**
 * @def UTF8
 * @brief Convert text to UTF8 string
 * @param text Text
 */
#define UTF8(text) websms::ConvertToUTF8((L##text))
#else  /* ifdef __cplusplus */
#define UTF8(text) ConvertToUTF8((L##text))
#endif  /* ifdef __cplusplus */
#else  /* ifdef __WIN32 */
#define EXPORT
#define UTF8(text) text
#endif  /* ifdef __WIN32 */

#ifdef __cplusplus
/**
 * @def EXTERN_C
 * @brief Export as C function
 */
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif

#ifdef __cplusplus
/**
 * @namespace websms
 * @brief Namespace for all classes, structs and functions of the websms.com
 * toolkit.
 */
namespace websms {
#endif

/**
 * @enum SenderAddressType
 * Possible sender address types
 */
typedef enum SenderAddressType {
  kNational,  ///< National number
  kInternational,  ///< International number
  kAlphanumeric,  ///< String
  kShortcode  ///< Short code
} SenderAddressType;

/**
 * Converts sender address type to string representation.
 * @param[in] type Sender adddress type
 * @return String representation
 */
EXTERN_C EXPORT const char* SenderAddressTypeToString(SenderAddressType type);

/**
 * Duplicates a string.
 * @param[in] text Text
 * @return Copy of text
 */
EXTERN_C EXPORT char* Strdup(const char* text);

/**
 * Delete a string.
 * @param[in] strptr Pointer to string
 */
EXTERN_C EXPORT void Strdel(const char* strptr);

/**
 * Returns library version.
 * @return Version
 */
EXTERN_C EXPORT const char* Version();

#ifdef _WIN32
/**
 * Convert wide character to UTF8 string (Windows only).
 * @param[in] text Text
 * @return UTF8 string. Must be freed by user.
 */
EXTERN_C EXPORT const char* ConvertToUTF8(const wchar_t* text);
#endif

#ifdef __cplusplus
}  // namespace websms
#endif

#endif  /* WEBSMS_MISC_H_ */
