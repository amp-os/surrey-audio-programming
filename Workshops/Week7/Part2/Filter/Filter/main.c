#include "biquad.h"
#include "buffer.h"
#include "wavhandling.h"

int main( int argc, char *argv[] ) {
    
    wav *inputFile = openWavRead( "noise.wav" );
    wav *outputFile = openWavWrite( "filtered.wav", inputFile );
    FILE *test = fopen( "test1.txt", "w" );
    
    biquad *filter = createBiquad();
    
    setCoefficients( filter, 1, -2, 1, 1, -0.2, 0.17 );
    
    const int bufferSize = 128;
    const int delaySize = 3;
    
    double buffer[ bufferSize ] = {0},
    delay1[ delaySize ] = {0},
    delay2[ delaySize ] = {0};
    
    sf_count_t count = 0;
    
    do {
        
        count = readWavDouble( inputFile, buffer, bufferSize );
        
        static int o = 0; // offset used as bufferSize % delaySize != 0, so each loop through the buffer will give an error in the delay index
        
        for ( int i = 0; i < count; ++i ) {
            
            delay1[ ( i + o ) % delaySize ] = buffer[ i ];
            
            buffer[ i ] += getb1(filter) * delay1[ ( i + o + delaySize - 1 ) % delaySize ];
            buffer[ i ] += getb2(filter) * delay1[ ( i + o + delaySize - 2 ) % delaySize ];
            
            buffer[ i ] -= geta1(filter) * delay2[ ( i + o + delaySize - 1 ) % delaySize ];
            buffer[ i ] -= geta2(filter) * delay2[ ( i + o + delaySize - 2 ) % delaySize ];
            
            delay2[ ( i + o ) % delaySize ] = buffer[ i ];
        }
        
        o = o + ( count % delaySize );
        
        writeWavDouble( outputFile, buffer, count );
        
        for ( int i = 0; i < count; ++i ) {
            fprintf( test, "%f\n", buffer[ i ] );
        }
        
    } while ( count == bufferSize );
    
    closeWav( inputFile );
    closeWav( outputFile );
    
    fclose( test );
    
    int frequencies[ 10 ] = { 50, 100, 200, 400, 1280, 2000, 5000, 8000, 10000, 15000 };
    
    printResponse( filter, frequencies, 10, 48000 );
    
    return 0;
}
