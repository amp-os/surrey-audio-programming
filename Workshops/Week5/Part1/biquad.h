#ifndef BIQUAD_H
#define BIQUAD_H

#include <complex.h>

#define g_sampleRate 44100.0
#define g_pi 3.14159265359
#define g_tau 2 * g_pi

typedef struct biquad_structure biquad;

biquad* createBiquad(void);
void destroyBiquad(biquad *filter);
void getCoefficients(biquad *filter);
double calculateResponse(biquad *filter, double frequency);
double complex calculateZ(double frequency);
double complex addCoefficients(float *c0, double complex z);
double calculatePhase(biquad *filter, double frequency);

#endif
