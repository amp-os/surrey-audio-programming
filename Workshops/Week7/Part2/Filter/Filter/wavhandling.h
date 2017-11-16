#ifndef wavhandling_h
#define wavhandling_h

#include <sndfile.h>

typedef struct wave_structure wav;

wav *openWav( char *filename, int mode );
void closeWav( wav *file );

int getSampleRate( wav *file );
int getChannelCount( wav *file );

sf_count_t readWavDouble( wav *file, double *buffer, int sizeOfBuffer );
void writeWavDouble( wav *file, double *buffer, sf_count_t items );

#endif
