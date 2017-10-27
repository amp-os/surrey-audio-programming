#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const double g_PI = 3.14159265359;
const double g_TAU = 2 * g_PI;

void printSinWave( double frequency, int samplingFrequency, double **offset );
void printArray( double *array, int length );

int main( int argc, char *argv[] ) {
    
    if ( argc != 2 )
        return 1;
    
    int sampleFrequency = atoi( argv[ 1 ] );
    
    double *outputArray = calloc( sampleFrequency * 2, sizeof( double ) );
    double *offset = outputArray;
    if ( outputArray == NULL )
        return 2;
    
    printSinWave( 3.5, sampleFrequency, &offset );

    printSinWave( 4, sampleFrequency, &offset );
    
    printArray( outputArray, 2 * sampleFrequency );
    
    free(outputArray);
    return 0;
}

void printSinWave( double frequency, int samplingFrequency, double **offset ) {
    static double phase = 0;
    
    for ( int h = 1; h * frequency < samplingFrequency / 2; h += 2) {
        
        for ( int i = 0; i < samplingFrequency; ++i ) {
            *( ( *offset ) + i ) +=  ( sin( fmod( ( g_TAU * h * frequency * i / samplingFrequency ) + phase, g_TAU ) ) / h );
        }
    }
    *offset = ( ( *offset ) + samplingFrequency );
    phase = fmod( ( g_TAU * frequency ) + phase, g_TAU );
    return;
}

void printArray( double *array, int length ) {
    for ( int i = 0; i < length; ++i ) {
        printf( "%f\n", *( array + i ) );
    }
    return;
}