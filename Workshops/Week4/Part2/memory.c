#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const double g_PI = 3.14159265359;
const double g_TAU = 2 * g_PI;

void printSinWave( double frequency, int samplingFrequency );

int main( int argc, char *argv[] ) {
	
	if ( argc != 2 )
		return 1;
	
	int sampleFrequency = atoi( argv[ 1 ] );
	
	printSinWave( 3.5, sampleFrequency );
	
	return 0;
}

void printSinWave( double frequency, int samplingFrequency ) {
	for ( int i = 0; i < samplingFrequency; ++i ) {
		printf( "%f\n", sin( fmod( ( g_TAU * frequency * i / samplingFrequency ), g_TAU ) ) );
	}
	return;
}