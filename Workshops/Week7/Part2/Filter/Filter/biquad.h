#ifndef biquad_h
#define biquad_h

typedef struct biquad_struct biquad;

biquad* createBiquad( void );
void destroyBiquad( biquad *filter );

void setCoefficients( biquad *filter, float b0, float b1, float b2, float a0, float a1, float a2 );
void printBiquad( biquad *filter );

#endif
