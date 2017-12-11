/**
 * Copyright (c) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#include <websms/misc.h>

namespace websms {

const char* SenderAddressTypeToString(SenderAddressType type) {
  switch(type) {
    case kNational: return "national";
    case kInternational: return "international";
    case kAlphanumeric: return "alphanumeric";
    case kShortcode: return "shortcode";
  }
  return NULL;
}

const char* Version() {
#ifdef VERSION
  return VERSION;
#else
  return "";
#endif
}

char* Strdup(const char* text) {
  if (text == NULL) {
    return NULL;
  }
  size_t size = strlen(text);
  char* buffer = new char[size + 1];
  memcpy(buffer, text, size);
  buffer[size] = '\0';
  return buffer;
}

void Strdel(const char* strptr) {
  if (strptr != NULL) {
    delete [] strptr;
  }
}

#ifdef _WIN32
const char* ConvertToUTF8(const wchar_t* text) {
  size_t size = WideCharToMultiByte(CP_UTF8, 0, text, -1, NULL, 0, NULL, NULL);
  char* buffer = new char[size];
  WideCharToMultiByte(CP_UTF8, 0, text, -1, buffer, size, NULL, NULL);
  return buffer;
}
#endif

}  /* namespace websms */
