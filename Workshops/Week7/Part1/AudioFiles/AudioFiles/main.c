//
//  main.c
//  AudioFiles
//
//  Created by Olly Seber on 09/11/2017.
//  Copyright © 2017 Olly Seber. All rights reserved.
//

#include <stdio.h>
#include <sndfile.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    
    SNDFILE *inputWav, *outputWav;
    SF_INFO inputInfo, outputInfo;
    
    inputWav = sf_open(argv[1], SFM_READ, &inputInfo);
    outputInfo = inputInfo;
    outputWav = sf_open(argv[2], SFM_WRITE, &outputInfo);
    
    printf("Enter a delay time in ms: ");
    int userInput;
    scanf("%i", &userInput);
    
    const int bufferSize = 128;
    int delaySize = (userInput * inputInfo.samplerate / 1000) + 1;
    
    double buffer[ bufferSize ] = {0};
    double *delayline = calloc(bufferSize, sizeof(double));
    
    sf_count_t count;
    int delayIndex = 0;
    
    do {
        
        count = sf_read_double(inputWav, buffer, bufferSize/inputInfo.channels);
        
        for ( int i = 0; i < count; ++i ) {
            delayline[ delayIndex ] = buffer[ i ] / (double) 2;
            buffer[ i ] += delayline[ delayIndex + 1 ];
            delayIndex = ( delayIndex + 1 ) % delaySize;
        }
        
        sf_write_double(outputWav, buffer, count);
        
    } while ( count == bufferSize );
    
    
    sf_close(inputWav);
    sf_close(outputWav);
    free(delayline);
    
    return 0;
}
