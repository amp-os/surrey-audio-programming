#include "biquad.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <complex.h>
#include "constants.h"

typedef struct biquad_struct {
    float b0;
    float b1;
    float b2;
    float a0;
    float a1;
    float a2;
} biquad;

double complex calculateZ( double frequency, int samplerate );
double complex addCoefficients( float *c0, double complex z );

biquad* createBiquad( void ) {
    biquad *filter = calloc( 1, sizeof( biquad ) );
    assert( filter );
    
    return filter;
}


void destroyBiquad( biquad *filter ) {
    assert( filter );
    free( filter );
}


void setCoefficients( biquad *filter, float b0, float b1, float b2, float a0, float a1, float a2 ) {
    assert( filter );
    
    filter->b0 = b0;
    filter->b1 = b1;
    filter->b2 = b2;
    filter->a0 = a0;
    filter->a1 = a1;
    filter->a2 = a2;
}


void printBiquad( biquad *filter ) {
    printf( "b0:\t%f\nb1:\t%f\nb2:\t%f\na0:\t%f\na1:\t%f\na2:\t%f\n",
           filter->b0, filter->b1, filter->b2, filter->a0, filter->a1, filter->a2 );
}


double calculateResponse( biquad *filter, double frequency, int samplerate ) {
    double complex H;
    double complex z;
    z = calculateZ( frequency, samplerate );
    
    H = addCoefficients( &( filter->b0 ), z ) / addCoefficients( &( filter->a0 ), z );
    
    return cabs( H );
}


double calculatePhase(biquad *filter, double frequency, int samplerate ) {
    double complex H;
    double complex z;
    z = calculateZ( frequency, samplerate );
    
    H = addCoefficients( &( filter->b0 ), z ) / addCoefficients( &( filter->a0 ), z );
    
    return carg( H ) / g_pi * 180;
}


double complex calculateZ( double frequency, int samplerate ) {
    double complex z = cexp( I * g_tau * frequency / samplerate );
    return z;
}


double complex addCoefficients( float *c0, double complex z ) {
    double complex sum = 0;
    for ( int i = 0; i < 3; ++i )
        sum += *( c0 + i ) * cpow( z, -1.0 * i );
    return sum;
}
