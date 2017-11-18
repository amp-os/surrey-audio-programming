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
    
    do {
        
        count = readWavDouble( inputFile, inputBuffer, bufferSize );
        
        static int o = 0; // offset used as bufferSize % delaySize != 0, so each loop through the buffer will give an error in the delay index
        
        for ( int i = 0; i < count; ++i ) {
            
            delay1[ ( i + o ) % delaySize ] = inputBuffer[ i ];
            
            outputBuffer[ i ] = inputBuffer[ i ];
            outputBuffer[ i ] += getb1(filter) * delay1[ ( i + o + delaySize - 1 ) % delaySize ];
            outputBuffer[ i ] += getb2(filter) * delay1[ ( i + o + delaySize - 2 ) % delaySize ];
            
            outputBuffer[ i ] -= geta1(filter) * delay2[ ( i + o + delaySize - 1 ) % delaySize ];
            outputBuffer[ i ] -= geta2(filter) * delay2[ ( i + o + delaySize - 2 ) % delaySize ];
            
            delay2[ ( i + o ) % delaySize ] = outputBuffer[ i ];
        }
        
        o = o + ( count % delaySize );
        
        writeWavDouble( outputFile, outputBuffer, count );
        
    } while ( count == bufferSize );
    
    closeWav( inputFile );
    closeWav( outputFile );
    
    int frequencies[ 10 ] = { 50, 100, 200, 400, 1280, 2000, 5000, 8000, 10000, 15000 };
    
    printResponse( filter, frequencies, 10, 48000 );
    
    return 0;
}
