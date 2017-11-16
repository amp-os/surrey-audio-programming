#include "biquad.h"

int main( int argc, char *argv[] ) {
    
    biquad *filter1 = createBiquad();
    setCoefficients(filter1, 1, 2, 3, 4, 5, 6);
    printBiquad(filter1);
    destroyBiquad(filter1);
    
    return 0;
}
