/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include "base64.h"

#include <stdint.h>

#include <string>

namespace websms {

const std::string Base64::kLookup =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char Base64::kPadding = '=';

}  /* namespace websms */
