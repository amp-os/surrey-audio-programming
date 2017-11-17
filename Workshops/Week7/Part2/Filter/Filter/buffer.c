#include "buffer.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct buffer_struct {
    double *data;
    int size;
    int readIndex;
    int writeIndex;
} buffer;


buffer* createBuffer( int size ) {
    buffer *buf = calloc( 1, sizeof(buffer) );
    assert( buf );
    
    buf->data = calloc( size + 1, sizeof(double) );
    assert( buf->data );
    
    buf->size = size + 1;
    buf->readIndex = 0;
    buf->writeIndex = 0;
    
    return buf;
}


void destroyBuffer( buffer *buf ) {
    assert( buf );
    assert( buf->data );
    free( buf->data );
    free( buf );
}


int writeItem( buffer *buf, double item ) {
    assert( buf );
    int next = buf->writeIndex + 1;
    if ( next >= buf->size ) {
        next = 0;
    }
    
    if ( next == buf->readIndex )
        return -1;
    
    buf->data[ buf->writeIndex ] = item;
    buf->writeIndex = next;
    
    return 0;
}


int readItem( buffer *buf, double *item ) {
    assert( buf );
    assert( item );
    
    if ( buf->readIndex == buf->writeIndex ) {
        return -1;
    }
    
    int next = buf->readIndex + 1;
    
    if ( next >= buf->size )
        next = 0;
    
    *item = buf->data[ buf->readIndex ];
    buf->readIndex = next;
    return 0;
}


void printBuffer( buffer *buf ) {
    assert( buf );
    for ( int i = 0; i < buf->size; ++i ) {
        printf( "Index %d\t%f\n", i, buf->data[ i ] );
    }
}
