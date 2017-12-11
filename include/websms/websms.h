/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 * @file websms.h
 * @brief Programs using the websms.com toolkit should include this header.
 */

#ifndef WEBSMS_WEBSMS_H_
#define WEBSMS_WEBSMS_H_

#ifdef __cplusplus
#include <websms/exceptions.h>
#include <websms/messages.h>
#include <websms/sms_client.h>
#else
#include <websms/capi.h>
#endif

#include <websms/arrays.h>
#include <websms/misc.h>
#include <websms/requests.h>
#include <websms/responses.h>
#include <websms/status_codes.h>

#endif  /* WEBSMS_WEBSMS_H_ */
