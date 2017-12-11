/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#ifndef WEBSMS_TEST_UTIL_H_
#define WEBSMS_TEST_UTIL_H_

#include <stdlib.h>

namespace websms {

const char* GetUrl();
const char* GetUsername(bool* ok);
const char* GetPassword(bool* ok);

}  /* namespace websms */

#endif  /* WEBSMS_TEST_UTIL_H_ */

