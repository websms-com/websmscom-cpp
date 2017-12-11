/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include <stdlib.h>

#include <iostream>

#include "utils.h"

namespace websms {

const char *GetUrl()
{
  return "https://api.websms.com/json";
}

const char* GetUsername(bool* ok) {
  char* user = getenv("WEBSMS_USERNAME");
  if (!user) {
    std::cout << ">>> WEBSMS_USERNAME not set. Skipping test..." << std::endl;
    *ok = false;
  }
  return user;
}

const char* GetPassword(bool* ok) {
  char* pass = getenv("WEBSMS_PASSWORD");
  if (!pass) {
    std::cout << ">>> WEBSMS_PASSWORD not set. Skipping test..." << std::endl;
    *ok = false;
  }
  return pass;
}

}  /* namespace websms */
