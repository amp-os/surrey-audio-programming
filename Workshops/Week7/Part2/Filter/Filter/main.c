#include "biquad.h"
#include "buffer.h"

int main( int argc, char *argv[] ) {
    
    const int sizeOfBuffer = 4;
    const int numberSteps = 3;
    
    buffer *buffer = createBuffer( sizeOfBuffer );
    
    for ( int i = 0; i < numberSteps; ++i ) {
        writeItem( buffer, i + 1 );
    }
    
    /* Error is caused if write head catches up to read head.
     * Therefore need to read some data to make enough space. */
    
    int clearspace = ( 2 * numberSteps ) - sizeOfBuffer;
    while ( clearspace-- >= 0 ) {
        double temporary;
        readItem(buffer, &temporary);
    }
    
    for ( int i = 0; i < numberSteps; ++i ) {
        writeItem( buffer, i + numberSteps );
    }
    
    printBuffer( buffer );
    
    destroyBuffer( buffer );
    
    return 0;
}
