//#include <stdio.h>
//
//#include <stdlib.h>
//
//#include <sndfile.h>
//
//#include <math.h>
//
//#include <portaudio.h>
//
//
//
//#define bufSize 128
//
//
//
//typedef float audioBuffer[bufSize];
//
//
//
//int main(int argc, const char* argv[])
//
//{
//
//    const char* sourcePath;
//
//
//
//    if (argc == 2)
//
//    {
//
//        sourcePath = argv[1];
//
//    }
//
//
//
//    audioBuffer buffer = {0};
//
//
//
//    SF_INFO sourceInfo;
//
//    SNDFILE* source = sf_open(sourcePath, SFM_READ, &sourceInfo);
//
//
//
//    Pa_Initialize();
//
//    PaStream* outputStream;
//
//    Pa_OpenDefaultStream(&outputStream, sourceInfo.channels, sourceInfo.channels, paFloat32, sourceInfo.samplerate, bufSize, NULL, NULL);
//
//    Pa_StartStream(outputStream);
//
//
//
//    int delayInMs = 0;
//
//
//
//    printf("input the delay time in milliseconds: ");
//
//
//
//    if (scanf("%i", &delayInMs) != 1)
//
//    {
//
//        exit(2);
//
//    }
//
//
//
//    //int sampleDelay = delayInMs  * (sourceInfo.samplerate / 1000) + 1;
//
//    int sampleDelay = 20001;
//
//    float* delayLine = calloc (sampleDelay, sizeof (float));
//
//
//
//
//
//    sf_count_t counter = bufSize;
//
//    int delayCounter = 0;
//
//
//
//    float averageLevel = 0;
//
//    float threshold = 0.000001;
//
//
//
//    do
//
//    {
//
//        counter = sf_read_float(source, buffer, bufSize);
//
//
//
//        for (int i = 0; i < bufSize; i++)
//
//        {
//
//            if (counter != bufSize && i >= counter)
//
//            {
//
//                buffer[i] = 0;
//
//            }
//
//
//
//            delayLine[delayCounter % sampleDelay] = buffer[i] + delayLine[(delayCounter + 1) % sampleDelay] * 0.8;
//
//            buffer[i] += delayLine[(delayCounter + 1) % sampleDelay] * 1.0;
//
//            delayCounter++;
//
//        }
//
//
//
//        averageLevel = 0;
//
//        for (int i = 0; i < sampleDelay; i++)
//
//        {
//
//            averageLevel += fabs (delayLine[i]);
//
//        }
//
//        averageLevel /= (float) sampleDelay;
//
//
//
//        Pa_WriteStream(outputStream, buffer, bufSize);
//
//    }
//
//    while(counter != 0 || averageLevel > threshold);
//
//
//
//    sf_close(source);
//
//
//
//    Pa_StopStream(outputStream);
//
//    Pa_CloseStream(outputStream);
//
//    Pa_Terminate();
//
//    return 0;
//
//}








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

double average( float *buffer, int count ) {
    double total = 0.0;
    for (int i = 0; i < count; ++i ){
        total += fabs( buffer[ i ] );
    }
    return total / (double) count;
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
    
    const int delaySize = 20000 * inputInfo.channels + inputInfo.channels;
    float buffer[ bufferSize ] = {0};
    float *delay = calloc( delaySize, sizeof( float ) );
    float feedback = 0.8;
    
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
        
        for ( int i = 0; i < bufferSize; ++i ) {
            if ( count != bufferSize && i >= count ) {
                buffer[ i ] = 0;
            }
            
            delay[ delayIndex ] = buffer[ i ] + feedback * delay[ ( delayIndex + inputInfo.channels ) % delaySize ];
            buffer[ i ] += delay[ ( delayIndex + inputInfo.channels ) % delaySize ];
            delayIndex = ( delayIndex + 1 ) % delaySize;
        }

        
        if ( Pa_WriteStream( stream, buffer, bufferSize / inputInfo.channels ) != paNoError ) {
            printf( "Issue streaming data!\n" );
            Pa_StopStream( stream );
            Pa_CloseStream( stream );
            Pa_Terminate();
            return 5;
        }
        
    } while ( count != 0 || average( delay, delaySize ) > 0.00001 );
    
//    do {
//        
//        for ( int i = 0; i < bufferSize; ++i ){
//            
//            delay[ delayIndex ] = feedback * delay[ ( delayIndex + inputInfo.channels ) % delaySize ];
//            buffer[ i ] = delay[ ( delayIndex + inputInfo.channels ) % delaySize ];
//            delayIndex = ( delayIndex + 1 ) % delaySize;
//            
//        }
//        
//        if ( Pa_WriteStream( stream, buffer, bufferSize / inputInfo.channels ) != paNoError ) {
//            printf( "Issue streaming end of delay!\n" );
//            Pa_StopStream( stream );
//            Pa_CloseStream( stream );
//            Pa_Terminate();
//            return 5;
//        }
//        
//    } while ( average( delay, delaySize ) > 0.00001 );
    
    
    
    
    
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





