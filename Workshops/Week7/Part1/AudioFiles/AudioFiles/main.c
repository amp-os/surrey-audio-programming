//
//  main.c
//  AudioFiles
//
//  Created by Olly Seber on 09/11/2017.
//  Copyright © 2017 Olly Seber. All rights reserved.
//

#include <stdio.h>
#include <sndfile.h>

int main(int argc, const char * argv[]) {
    
    SNDFILE *inputWav, *outputWav;
    SF_INFO inputInfo, outputInfo;
    
    inputWav = sf_open(argv[1], SFM_READ, &inputInfo);
    outputInfo = inputInfo;
    outputWav = sf_open(argv[2], SFM_WRITE, &outputInfo);
    
    const int bufferSize = 128;
    const int delaySize = 100 + 1;
    
    double buffer[ bufferSize ] = {0};
    double delayline[ delaySize ] = {0};
    
    sf_count_t count;
    
    do {
        
        count = sf_read_double(inputWav, buffer, bufferSize/inputInfo.channels);
        
        for ( int i = 0; i < count; ++i ) {
            delayline[ i % delaySize ] = buffer[ i ] / (double) 2;
            buffer[ i ] += delayline[ ( i + 1 ) % delaySize ];
        }
        
        sf_write_double(outputWav, buffer, count);
        
    } while ( count == bufferSize );
    
    
    sf_close(inputWav);
    sf_close(outputWav);
    
    return 0;
}
