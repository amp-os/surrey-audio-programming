//
//  test.cpp
//  Tests
//
//  Created by Olly Seber on 07/10/2017.
//  Copyright © 2017 Olly Seber. All rights reserved.
//

#include "CppUTest/TestHarness.h"
#include "../../Code/Code/main.c"

TEST_GROUP(aTestGroup)
{
};

TEST(aTestGroup, aTest)
{
    int x = test_func();
    CHECK_EQUAL(1, x);
}
