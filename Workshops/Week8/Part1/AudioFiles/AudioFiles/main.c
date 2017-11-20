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
    
    float buffer[ bufferSize ];
    
    sf_count_t count;
    
    if ( Pa_StartStream( stream ) != paNoError ) {
        printf( "Issue starting stream!\n" );
        Pa_CloseStream( stream );
        Pa_Terminate();
        return 4;
    }
    
    do {
        
        count = sf_read_float( inputFile, buffer, bufferSize / inputInfo.channels );
        
//        for ( int i = 0; i < count; ++i ) {
//            buffer[i] = buffer[i] / (double) 2;
//        }
        
        if ( Pa_WriteStream( stream, buffer, count / inputInfo.channels ) != paNoError ) {
            printf( "Issue streaming data!\n" );
            Pa_StopStream( stream );
            Pa_CloseStream( stream );
            Pa_Terminate();
            return 5;
        }
        
        
    } while ( count != 0 );
    
    sf_close( inputFile );
    
    Pa_StopStream( stream );
    
    Pa_CloseStream( stream );
    
    Pa_Terminate();
    
    return 0;
}


