//
//  main.c
//  AudioFiles
//
//  Created by Olly Seber on 09/11/2017.
//  Copyright © 2017 Olly Seber. All rights reserved.
//

#include <stdio.h>
#include <sndfile.h>
#include <portaudio.h>
#include <stdlib.h>
#include <math.h>

double movingAverage( float sample ) {
    const int window = 100;
    static float buffer[ window ] = {0.5};
    static int count = 0;
    float total = 0;
    
    
    buffer[ count ] = fabs( sample );
    
    for ( int i = 0; i < window; ++i ) {
        total += buffer[ i ];
    }
    
    count = ( count + 1 ) % window;
    
    return total / window;
}

int main(int argc, const char * argv[]) {
    
    SNDFILE *inputFile;
    SF_INFO inputInfo;
    
    const int bufferSize = 128;
    
    inputFile = sf_open( argv[ 1 ], SFM_READ, &inputInfo );
    if ( inputFile == NULL ) {
        printf( "Issue opening input file!\n" );
        return 1;
    }
    
    if ( Pa_Initialize() != paNoError ) {
        printf( "Issue initialising portaudio!\n" );
        return 2;
    }
    
    PaStream *stream;
    
    if ( Pa_OpenDefaultStream( &stream, 0, inputInfo.channels, paFloat32, inputInfo.samplerate, bufferSize / inputInfo.channels, NULL, NULL ) != paNoError ) {
        printf( "Issue opening stream!\n" );
        Pa_Terminate();
        return 3;
    }
    
    const int delaySize = 20000 * inputInfo.channels;
    float buffer[ bufferSize ] = {0};
    float *delay = calloc( delaySize + inputInfo.channels, sizeof( float ) );
    float feedback = 0.7;
    
    sf_count_t count;
    
    if ( Pa_StartStream( stream ) != paNoError ) {
        printf( "Issue starting stream!\n" );
        Pa_CloseStream( stream );
        Pa_Terminate();
        return 4;
    }
    
    int delayIndex = 0;
    
    do {
        
        count = sf_read_float( inputFile, buffer, bufferSize );
        
        for ( int i = 0; i < count; ++i ) {
            delay[ delayIndex ] = buffer[ i ] + feedback * delay[ ( delayIndex + inputInfo.channels ) % delaySize ];
            buffer[ i ] += delay[ ( delayIndex + inputInfo.channels ) % delaySize ];
            delayIndex = ( delayIndex + 1 ) % delaySize;
        }
        
        if ( Pa_WriteStream( stream, buffer, count / inputInfo.channels ) != paNoError ) {
            printf( "Issue streaming data!\n" );
            Pa_StopStream( stream );
            Pa_CloseStream( stream );
            Pa_Terminate();
            return 5;
        }
        
    } while ( count != 0 );
    
    float avg = 0;
    
    do {
        
        for ( int i = 0; i < delaySize; ++i ){
        
            buffer[ i % bufferSize ] = delay[ ( delayIndex + inputInfo.channels ) % delaySize ];
            
            if ( i % bufferSize == 0 ) {
                if ( Pa_WriteStream( stream, buffer, bufferSize / inputInfo.channels ) != paNoError ) {
                    printf( "Issue streaming end of delay!\n" );
                    Pa_StopStream( stream );
                    Pa_CloseStream( stream );
                    Pa_Terminate();
                    return 5;
                }
            }
            
            avg = movingAverage( delay[ i ] );
            delay[ delayIndex ] = feedback * delay[ delayIndex ];
            delayIndex = ( delayIndex + 1 ) % delaySize;
        }
    } while ( avg > 0.00001 );
    
    
    
    
    
//    /* Flush delay */
//    for ( int i = 0; i < delaySize; ++i ) {
//        buffer[ i % bufferSize ] = delay[ delayIndex + 1 ];
//        delayIndex = ( delayIndex + 1 ) % delaySize;
//        
//        if ( i % bufferSize == 0 ) {
//            if ( Pa_WriteStream( stream, buffer, ( i % bufferSize ) / inputInfo.channels ) != paNoError ) {
//                printf( "Issue streaming end of delay!\n" );
//                Pa_StopStream( stream );
//                Pa_CloseStream( stream );
//                Pa_Terminate();
//                return 5;
//            }
//        }
//            
//        
//    }
    
    free( delay );
    
    sf_close( inputFile );
    
    Pa_StopStream( stream );
    
    Pa_CloseStream( stream );
    
    Pa_Terminate();
    
    return 0;
}


