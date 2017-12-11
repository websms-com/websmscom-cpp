/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include "json.h"

#include <stdint.h>

#include <string>
#include <vector>

#include <jansson.h>

#include <websms/misc.h>

namespace websms {

Json::Json()
    : root_(json_object()) {
}

Json::~Json() {
  if (root_ != NULL) {
    json_decref(root_);
  }
}

bool Json::Parse(const std::string& data) {
  if (root_ != NULL) {
    json_decref(root_);
    root_ = NULL;
  }
  return (root_ = json_loads(data.c_str(), 0, NULL)) != NULL;
}

void Json::Add(const std::string& key, int value) {
  json_object_set_new(root_, key.c_str(), json_integer(value));
}

void Json::Add(const std::string& key, uint32_t value) {
  json_object_set_new(root_, key.c_str(), json_integer(value));
}

void Json::Add(const std::string& key, bool value) {
  json_object_set_new(root_, key.c_str(), value ? json_true() : json_false());
}

void Json::Add(const std::string& key, const char* value) {
  if (value != NULL) {
    json_object_set_new(root_, key.c_str(), json_string(value));
  }
}

void Json::Add(const std::string& key, const std::vector<int64_t>& value) {
  json_t* array = json_array();
  for (size_t i = 0; i < value.size(); ++i) {
    json_array_append_new(array, json_integer(value[i]));
  }
  json_object_set_new(root_, key.c_str(), array);
}

void Json::Add(const std::string& key, const std::vector<std::string>& value) {
  json_t* array = json_array();
  for (size_t i = 0; i < value.size(); ++i) {
    json_array_append_new(array, json_string(value[i].c_str()));
  }
  json_object_set_new(root_, key.c_str(), array);
}

bool Json::Get(const std::string& key, int* data) const {
  json_t* value = json_object_get(root_, key.c_str());
  if (value != NULL && json_is_integer(value)) {
    *data = static_cast<int>(json_integer_value(value));
    return true;
  }
  return false;
}

bool Json::Get(const std::string& key, bool* data) const {
  json_t* value = json_object_get(root_, key.c_str());
  if (value != NULL && json_is_boolean(value)) {
    *data = json_is_true(value) ? true : false;
    return true;
  }
  return false;
}

bool Json::Get(const std::string& key, const char** data) const {
  json_t* value = json_object_get(root_, key.c_str());
  if (value != NULL && json_is_string(value)) {
    const char* source = json_string_value(value);
    *data = Strdup(source);
    return true;
  }
  return false;
}

std::string Json::GetAsString() const {
  std::string dump;
  json_dump_callback(root_, &Json::DumpCallback, &dump, JSON_COMPACT);
  return dump;
}

int Json::DumpCallback(const char *buffer, size_t size, void *data) {
  std::string* dump = static_cast<std::string*>(data);
  dump->append(buffer, size);
  return 0;
}

}  /* namespace websms */
