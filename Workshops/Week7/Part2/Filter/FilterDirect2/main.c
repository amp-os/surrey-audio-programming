#include "biquad.h"
#include "buffer.h"
#include "wavhandling.h"

int main( int argc, char *argv[] ) {
    
    wav *inputFile = openWavRead( "noise.wav" );
    wav *outputFile = openWavWrite( "filtered2.wav", inputFile );
    
    biquad *filter = createBiquad();
    
    setCoefficients( filter, 1, -2, 1, 1, -0.2, 0.17 );
    
    const int bufferSize = 128;
    const int delaySize = 3;
    
    double inputBuffer[ bufferSize ] = {0},
    outputBuffer[ bufferSize ] = {0},
    delay[ delaySize ] = {0};
    
    sf_count_t count = 0;
    
    int j = delaySize; // delay index
    
    do {
        
        count = readWavDouble( inputFile, inputBuffer, bufferSize );
        
        for (int i = 0; i < count; ++i, ++j ) {
            
            delay[ j % delaySize ] = inputBuffer[ i ] - ( geta1( filter ) * delay[ ( j - 1 ) % delaySize ] ) - ( geta2( filter ) * delay[ ( j - 2 ) % delaySize ] );
            
            outputBuffer[ i ] = ( getb0( filter ) * delay[ j % delaySize ] ) + ( getb1( filter ) * delay[ ( j - 1 ) % delaySize ] ) + ( getb2( filter ) * delay[ ( j - 2 ) % delaySize ] );
            
        }
        
        writeWavDouble( outputFile, outputBuffer, count );
        
        j = ( j % delaySize ) + delaySize;
        
    } while ( count == bufferSize );
    
    closeWav( inputFile );
    closeWav( outputFile );
    
    int frequencies[ 10 ] = { 50, 100, 200, 400, 1280, 2000, 5000, 8000, 10000, 15000 };
    
    printResponse( filter, frequencies, 10, 48000 );
    
    return 0;
}
