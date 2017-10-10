//
//  main.c
//  dBconversion
//
//  Created by Olly Seber on 07/10/2017.
//  Copyright © 2017 Olly Seber. All rights reserved.
//

#include <stdio.h>
#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char** av)
{
    return CommandLineTestRunner::RUN_ALL_TESTS(ac, av);
}
