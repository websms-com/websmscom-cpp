/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#ifndef WEBSMS_JSON_H_
#define WEBSMS_JSON_H_

#include <stdint.h>

#include <string>
#include <vector>

#include <jansson.h>

#include <websms/arrays.h>
#include <websms/misc.h>

namespace websms {

/**
 * @class Json
 * @brief Class for handling JSON objects. Uses jannson, a C library for
 * encoding, decoding and manipulating JSON data
 * (http://www.digip.org/jansson/).
 */
class Json {
 public:
  Json();
  ~Json();

  /**
   * Parses JSON string.
   * @param[in] data JSON string
   * @return Returns false on error.
   */
  bool Parse(const std::string& data);

  /**
   * Adds key/value pair.
   * @param[in] key Key
   * @param[in] value Value
   */
  void Add(const std::string& key, int value);

  /**
   * Adds key/value pair.
   * @param[in] key Key
   * @param[in] value Value
   */
  void Add(const std::string& key, uint32_t value);

  /**
   * Adds key/value pair.
   * @param[in] key Key
   * @param[in] value Value
   */
  void Add(const std::string& key, bool value);

  /**
   * Adds key/value pair.
   * @param[in] key Key
   * @param[in] value Value
   */
  void Add(const std::string& key, const char* value);

  /**
   * Adds key/value pair.
   * @param[in] key Key
   * @param[in] value Value
   */
  void Add(const std::string&, const std::vector<int64_t>& value);

  /**
   * Adds key/value pair.
   * @param[in] key Key
   * @param[in] value Value
   */
  void Add(const std::string&, const std::vector<std::string>& value);

  /**
   * Searches value for key and sets target.
   * @param[in] key Key
   * @param[out] target Target
   * @return Entry found?
   */
  bool Get(const std::string&, int* target) const;

  /**
   * Searches value for key and sets target.
   * @param[in] key Key
   * @param[out] target Target
   * @return Entry found?
   */
  bool Get(const std::string&, bool* target) const;

  /**
   * Searches value for key and sets target.
   * @param[in] key Key
   * @param[out] target Target
   * @return Entry found?
   */
  bool Get(const std::string&, const char** target) const;

  /**
   * Returns JSON string.
   * @return JSON string
   */
  std::string GetAsString() const;

 private:
  static int DumpCallback(const char *buffer, size_t size, void *data);
  json_t* root_;
  DISALLOW_COPY_AND_ASSIGN(Json)
};

}  /* namespace websms */

#endif  /* WEBSMS_JSON_H_ */
