#ifndef buffer_h
#define buffer_h

typedef struct buffer_struct buffer;

buffer* createBuffer( int size );
void destroyBuffer( buffer *buf );

int writeItem( buffer *buf, double item );
int readItem( buffer *buf, double *item );

void printBuffer( buffer *buf );

#endif
