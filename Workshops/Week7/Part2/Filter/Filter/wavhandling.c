#include "wavhandling.h"
#include <stdlib.h>
#include <assert.h>

typedef struct wave_structure {
    SNDFILE *audioFile;
    SF_INFO infoFile;
} wav;


wav *openWavRead( char *filename ) {
    wav *file = calloc( 1, sizeof( wav ) );
    assert( file );
    
    file->audioFile = sf_open( filename, SFM_READ, &file->infoFile );
    
    return file;
}



wav *openWavWrite( char *filename, wav *filterSettings ) {
    wav *file = calloc( 1, sizeof( wav ) );
    assert( file );
    
    file->infoFile = filterSettings->infoFile;
    
    file->audioFile = sf_open( filename, SFM_WRITE, &file->infoFile );
    
    return file;
}


void closeWav( wav *file ) {
    assert( file );
    sf_close( file->audioFile );
}


int getSampleRate( wav *file ) {
    assert( file );
    return file->infoFile.samplerate;
}


int getChannelCount( wav *file ) {
    assert( file );
    return file->infoFile.channels;
}


sf_count_t readWavDouble( wav *file, double *buffer, int sizeOfBuffer ) {
    assert( file );
    return sf_read_double( file->audioFile, buffer, sizeOfBuffer/file->infoFile.channels );
}


void writeWavDouble( wav *file, double *buffer, sf_count_t items ) {
    assert( file );
    sf_write_double( file->audioFile, buffer, items );
}
