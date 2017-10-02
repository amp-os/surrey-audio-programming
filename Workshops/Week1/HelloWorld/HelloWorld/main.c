//
//  main.c
//  HelloWorld
//
//  Created by Olly Seber on 02/10/2017.
//  Copyright © 2017 Olly Seber. All rights reserved.
//

#include <stdio.h> // Required for printf

int main(int argc, const char * argv[]) { // Inputs to main
    // insert code here...
    printf("Hello, World!\n");
    const char * arg1 = argv[0];
    const char * arg2 = argv[1];
    const char * arg3 = argv[2];
    const char * arg4 = argv[3];
    
    printf("%s", arg1);
    printf("\n");
    printf("%c", *arg1);
    printf("\n");
    
    return 0; // Output of main
}
