#include "biquad.h"
#include <math.h>
#include <complex.h>
#include <stdlib.h>


typedef struct biquad_structure {
    float b0;
    float b1;
    float b2;
    float a0;
    float a1;
    float a2;
} biquad;


biquad* createBiquad( void ) {
	biquad* filter = malloc( sizeof( biquad ) );
	if ( filter == NULL )
		exit( 1 );
	return filter;
}


void destroyBiquad( biquad *filter ) {
	free( filter );
}


void getCoefficients(biquad *filter) {
    filter->b0 = 1;
    filter->b1 = -2;
    filter->b2 = 1;
    filter->a0 = 1;
    filter->a1 = -0.2;
    filter->a2 = 0.17;
    return;
}


double calculateResponse(biquad *filter, double frequency) {
    double complex H;
    double complex z;
    z = calculateZ(frequency);
    
    H = addCoefficients(&(filter->b0), z) / addCoefficients(&(filter->a0), z);
    
    return cabs(H);
}


double calculatePhase(biquad *filter, double frequency) {
	double complex H;
	double complex z;
	z = calculateZ(frequency);
	
	H = addCoefficients(&(filter->b0), z) / addCoefficients(&(filter->a0), z);
	
	return carg(H) / g_pi * 180;
}


double complex calculateZ(double frequency) {
    double complex z = cexp(I * g_tau * frequency / g_sampleRate);
    return z;
}


double complex addCoefficients(float *c0, double complex z) {
    double complex sum = 0;
    for(int i = 0; i < 3; ++i)
        sum += *(c0+i) * cpow(z, -1.0 * i);
    return sum;
}
