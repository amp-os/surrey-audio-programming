#ifndef biquad_h
#define biquad_h

typedef struct biquad_struct biquad;

biquad* createBiquad( void );
void destroyBiquad( biquad *filter );

void setCoefficients( biquad *filter, float b0, float b1, float b2, float a0, float a1, float a2 );
void printBiquad( biquad *filter );

double calculateResponse( biquad *filter, double frequency, int samplerate );
double calculatePhase(biquad *filter, double frequency, int samplerate );

double getb0( biquad *filter );
double getb1( biquad *filter );
double getb2( biquad *filter );
double geta0( biquad *filter );
double geta1( biquad *filter );
double geta2( biquad *filter );

void printResponse( biquad *filter, int *frequencies, int count, int samplerate );

#endif
