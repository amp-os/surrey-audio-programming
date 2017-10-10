//
//  test.c
//  dBconversion
//
//  Created by Olly Seber on 07/10/2017.
//  Copyright © 2017 Olly Seber. All rights reserved.
//

#include <stdio.h>
#include "CppUTest/TestHarness.h"
#include "/Users/OllySeber/GoogleDrive/Uni/ModuleNotes/FinalYear/AudioProgramming/AudioProgrammingGit/Workshops/Week1/dBconversion/dBconversion/main.c"

TEST_GROUP(dBConversionTests)
{
};

TEST(dBConversionTests, FirstTest)
{
    int x = firstTest(1);
    CHECK_EQUAL(2, x); // Add 1
}
