//
//  main.c
//  dBconversion
//
//  Created by Olly Seber on 06/10/2017.
//  Copyright © 2017 Olly Seber. All rights reserved.
//

#include <stdio.h>
#include <math.h> // For pow()
#include <stdlib.h> // For atoi()

int main(int argc, const char * argv[]) {
    if(argc < 2){
        printf("No argument supplied! I die gracefully.\n");
        return 1;
    }
    
    const int dB = atoi(argv[1]);
    const double gain = pow(10, dB / 20.0);
    
    printf("%idB gain = %f linear gain\nThis is %.0f%%\nThe dB value is stored at %p, the linear gain at %p, and the percentage is an rvalue.\n", dB, gain, gain*100, &dB, &gain);
    
    return 0;
}

int firstTest(const int a)
{
    return a + 1;
}
