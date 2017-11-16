#include "biquad.h"
#include "buffer.h"

int main( int argc, char *argv[] ) {
    
    buffer *buffer = createBuffer( 5 );
    
    double *ptr = getWritePosition( buffer, 3 );
    
    for ( int i = 0; i < 3; ++i ) {
        *( ptr + i ) = i;
    }
    
    printBuffer( buffer );
    
    ptr = getWritePosition( buffer, 3 );
    
    for ( int i = 0; i < 3; ++i ) {
        *( ptr + i ) = i + 3 ;
        // Doesn't work yet as keeps writing on. Need some way of writing in cycle.
    }
    
    printBuffer( buffer );
    
    destroyBuffer( buffer );
    
    return 0;
}
