#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

const double g_PI = 3.14159265359;
const double g_TAU = 2 * g_PI;

void printSquareWave( double frequency, int samplingFrequency, double *offset, char *output );

bool writeToFile( const char *fileName, void *ptr, size_t size, size_t nmemb );

int main( int argc, char *argv[] ) {
    
    if ( argc != 3 )
        return 1;
    
    int sampleFrequency = atoi( argv[ 1 ] );
    
    printf( "Selected sample rate: %d\n", sampleFrequency );
    
    FILE *file = fopen( argv[ 2 ], "r" );
    if ( file == NULL ) {
    	remove( argv[2] );
    }
    else {
    	fclose ( file );
    }
    	
    
    double *outputArray = calloc( 1, sizeof( double ) );
    if ( outputArray == NULL )
        return 2;
    
    printSquareWave( 350, sampleFrequency, outputArray, argv[ 2 ] );
    
    printf( "File %s was closed successfully!\n", argv[ 2 ] );
    free( outputArray );
    return 0;
}

void printSquareWave( double frequency, int samplingFrequency, double *offset, char *output ) {
    static double phase = 0;
    
    for ( int i = 0; i < 10 * samplingFrequency; ++i ) {
        
        for ( int h = 1; h * frequency < samplingFrequency / 2; h += 2 ) {
            *offset +=  ( sin( fmod( ( g_TAU * h * frequency * i / samplingFrequency ) + phase, g_TAU ) ) / h );
        }
        
        if ( !writeToFile( output, offset, sizeof( double ), sizeof( *offset ) / sizeof( double ) ) ) {
    		printf( "Could not write to file!\n" );
    		exit( 4 );
    	}
    }
   
    phase = fmod( ( g_TAU * frequency ) + phase, g_TAU );
    return;
}

bool writeToFile( const char *fileName, void *ptr, size_t size, size_t nmemb ) {
	FILE *f = fopen( fileName, "a" );
	if ( f == NULL )
		return false;
	
	if ( fwrite( ptr, size, nmemb, f ) != nmemb )
		return false;
	
	if ( fclose( f ) != 0 )
		return false;
	
	return true;
}
