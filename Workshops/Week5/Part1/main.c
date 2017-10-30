#include <stdio.h>
#include "biquad.h"


int main(int argc, char *argv[]) {
    
    int frequencyArray[] = {50, 100, 200, 400, 800, 1600, 3200, 6400, 12800, 20000};
    
    biquad *filter1 = createBiquad();
    
    getCoefficients(filter1);
    
    for(int i = 0; i < 10; ++i) {
        printf("%d\t%f\t%f\n", frequencyArray[i], calculateResponse(filter1, frequencyArray[i]),
        	calculatePhase(filter1, frequencyArray[i]));
    }
    
    destroyBiquad(filter1);
    
    return 0;
}
