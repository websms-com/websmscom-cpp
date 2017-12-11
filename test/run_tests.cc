/**
 * Copyright (C) 2012, sms.at mobile internet services gmbh
 *
 * @author Markus Opitz
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
