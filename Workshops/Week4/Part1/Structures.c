#include <stdio.h>
#include <math.h>
#include <complex.h>

const double g_sampleRate = 44100.0;
const double g_pi = 3.14159265359;
const double g_tau = 2 * g_pi;

typedef struct biquad_structure {
    float b0;
    float b1;
    float b2;
    float a0;
    float a1;
    float a2;
} biquad;

void getCoefficients(biquad *filter);
double calculateResponse(biquad filter, double frequency);
double complex calculateZ(double frequency);
double complex addCoefficients(float *c0, double complex z);

int main(int argc, char *argv[]) {
    
    int frequencyArray[] = {50, 100, 200, 400, 800, 1600, 3200, 6400, 12800, 20000};
    
    biquad filter1;
    
    getCoefficients(&filter1);
    
    for(int i = 0; i < 10; ++i) {
        printf("%d\t%f\n", frequencyArray[i], calculateResponse(filter1, frequencyArray[i]));
    }
    
    return 0;
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

double calculateResponse(biquad filter, double frequency) {
    double complex H;
    double complex z;
    z = calculateZ(frequency);
    
    H = addCoefficients(&filter.b0, z) / addCoefficients(&filter.a0, z);
    
    return cabs(H);
    
}

double complex calculateZ(double frequency) {
    double complex z = cexp(I * g_tau * frequency / g_sampleRate);
    //printf("%f + %fi\n", creal(z), cimag(z));
    return z;
}

double complex addCoefficients(float *c0, double complex z) {
    double complex sum = 0;
    for(int i = 0; i < 3; ++i)
        sum += *(c0+i) * cpow(z, -1.0 * i);
    //printf("%f + %fi\n", creal(sum), cimag(sum));
    return sum;
}