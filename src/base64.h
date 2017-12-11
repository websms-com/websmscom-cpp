/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#ifndef WEBSMS_BASE64_H_
#define WEBSMS_BASE64_H_

#include <stdint.h>

#include <string>
#include <vector>

namespace websms {

/**
 * @class Base64
 * @brief Provides Base64 encoding and decoding based on
 * http://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64.
 */
class Base64 {
 public:
  /**
   * Encodes data.
   * @param[in] input Input data
   * @tparam T Input type
   * @return Encoded string
   */
  template<class T>
  static std::string Encode(const T& input) {
    std::string encoded;
    encoded.reserve(((input.size() / 3) + (input.size() % 3 > 0)) * 4);
    int64_t temp;
    typename T::const_iterator cursor = input.begin();
    for (size_t i = 0; i < input.size() / 3; ++i) {
      temp = (*cursor++) << 16;
      temp += (*cursor++) << 8;
      temp += (*cursor++);
      encoded.append(1, kLookup[(temp & 0x00FC0000) >> 18]);
      encoded.append(1, kLookup[(temp & 0x0003F000) >> 12]);
      encoded.append(1, kLookup[(temp & 0x00000FC0) >> 6]);
      encoded.append(1, kLookup[(temp & 0x0000003F)]);
    }
    switch (input.size() % 3) {
      case 1: {
        temp = (*cursor++) << 16;
        encoded.append(1, kLookup[(temp & 0x00FC0000) >> 18]);
        encoded.append(1, kLookup[(temp & 0x0003F000) >> 12]);
        encoded.append(2, kPadding);
        break;
      }
      case 2: {
        temp = (*cursor++) << 16;
        temp += (*cursor++) << 8;
        encoded.append(1, kLookup[(temp & 0x00FC0000) >> 18]);
        encoded.append(1, kLookup[(temp & 0x0003F000) >> 12]);
        encoded.append(1, kLookup[(temp & 0x00000FC0) >> 6]);
        encoded.append(1, kPadding);
        break;
      }
    }
    return encoded;
  }

  /**
   * Decodes Base64 string.
   * @param[in] input[in] Encoded string
   * @param[out] decoded[out] Output data
   * @tparam T Output type
   * @return Output Data, NULL on error
   */
  template<class T>
  static T* Decode(const std::string& input, T* decoded) {
    if (input.length() % 4)
      return NULL;
    size_t padding = 0;
    if (input.length()) {
      if (input[input.length() - 1] == kPadding) {
        padding++;
      }
      if (input[input.length() - 2] == kPadding) {
        padding++;
      }
    }
    decoded->reserve(((input.length() / 4) * 3) - padding);
    int64_t temp = 0;
    std::string::const_iterator cursor = input.begin();
    while (cursor < input.end()) {
      for (size_t quantumPosition = 0; quantumPosition < 4;
          quantumPosition++) {
        temp <<= 6;
        if (*cursor >= 0x41 && *cursor <= 0x5A) {
          temp |= *cursor - 0x41;
        } else if (*cursor >= 0x61 && *cursor <= 0x7A) {
          temp |= *cursor - 0x47;
        } else if (*cursor >= 0x30 && *cursor <= 0x39) {
          temp |= *cursor + 0x04;
        } else if (*cursor == 0x2B) {
          temp |= 0x3E;
        } else if (*cursor == 0x2F) {
          temp |= 0x3F;
        } else if (*cursor == kPadding) {
          switch (input.end() - cursor) {
            case 1: {
              decoded->push_back((temp >> 16) & 0x000000FF);
              decoded->push_back((temp >> 8) & 0x000000FF);
              return decoded;
            }
            case 2: {
              decoded->push_back((temp >> 10) & 0x000000FF);
              return decoded;
            }
            default: {
              return NULL;
            }
          }
        } else {
          return NULL;
        }
        ++cursor;
      }
      decoded->push_back((temp >> 16) & 0x000000FF);
      decoded->push_back((temp >> 8) & 0x000000FF);
      decoded->push_back((temp) & 0x000000FF);
    }
    return decoded;
  }

 private:
  static const std::string kLookup;
  static const char kPadding;
  Base64() {
  }
};

} /* namespace websms */
#endif  /* WEBSMS_BASE64_H_ */
