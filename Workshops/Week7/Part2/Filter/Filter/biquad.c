#include "biquad.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct biquad_struct {
    float b0;
    float b1;
    float b2;
    float a0;
    float a1;
    float a2;
} biquad;


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
