#include "biquad.h"
#include "buffer.h"
#include "wavhandling.h"

int main( int argc, char *argv[] ) {
    
    wav *inputFile = openWavRead( "noise.wav" );
    wav *outputFile = openWavWrite( "filtered.wav", inputFile );
    
    biquad *filter = createBiquad();
    
    setCoefficients( filter, 1, -2, 1, 1, -0.2, 0.17 );
    
    const int bufferSize = 128;
    const int delaySize = 3;
    
    double inputBuffer[ bufferSize ] = {0},
        outputBuffer[ bufferSize ] = {0},
    delay1[ delaySize ] = {0},
    delay2[ delaySize ] = {0};
    
    sf_count_t count = 0;
    
    int outputBufferIndex = 0, delay1Index = 0, delay2Index = 0;
    
    do {
        
        count = readWavDouble( inputFile, inputBuffer, bufferSize );
        
        for ( int i = 0; i < count; ++i ) {
            
            delay1[ delay1Index ] = inputBuffer[ i ];
            
            outputBuffer[ outputBufferIndex ] = inputBuffer[ i ];
            outputBuffer[ outputBufferIndex ] += getb1(filter) * delay1[ ( delay1Index + delaySize - 1 ) % delaySize ];
            outputBuffer[ outputBufferIndex ] += getb2(filter) * delay1[ ( delay1Index + delaySize - 2 ) % delaySize ];
            
            outputBuffer[ outputBufferIndex ] -= geta1(filter) * delay2[ ( delay2Index + delaySize - 1 ) % delaySize ];
            outputBuffer[ outputBufferIndex ] -= geta2(filter) * delay2[ ( delay2Index + delaySize - 2 ) % delaySize ];
            
            delay2[ delay2Index ] = outputBuffer[ i ];
            
            outputBufferIndex = ( outputBufferIndex + 1 ) % bufferSize;
            delay1Index = ( delay1Index + 1 ) % delaySize;
            delay2Index = ( delay2Index + 1 ) % delaySize;
        }
        
        writeWavDouble( outputFile, outputBuffer, count );
        
    } while ( count == bufferSize );
    
    closeWav( inputFile );
    closeWav( outputFile );
    
    int frequencies[ 10 ] = { 20, 80, 320, 640, 1280, 2000, 5000, 8000, 10000, 15000 };
    
    printResponse( filter, frequencies, 10, 48000 );
    
    return 0;
}
