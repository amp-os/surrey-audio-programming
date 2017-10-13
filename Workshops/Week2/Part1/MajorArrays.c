#include <stdio.h>
#include <stdbool.h>

char *noteNames[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

char* midiIntToString(int midiInteger)
{
	return noteNames[midiInteger % 12];
}

bool getInt(int startingNote)
{
	char str[10];
	fgets(str, 10, stdin);
	startingNote = atoi(str);
	if(!a)
		printf("I can't interpret this as an integer!\n");
	return a;
}

int main(int argc, char *argv[])
{
	unsigned int startingNote = 128;
	
	do{
		do{
			printf("Please enter a starting note as an integer: ");
		}while(!getInt(startingNote));
		
		if(startingNote > 127)
			printf("This out of the standard midi note range (0-127)\n");
		
	}while(startingNote > 127);
		
	int indexes[] = {0, 2, 4, 5, 7, 9, 11};
	
	for(int i = 0; i < 7; ++i){
		printf("%s ", noteNames[(startingNote + indexes[i]) % 12]);
	}
	
	printf("are the notes of the major scale starting on %s\n", midiIntToString(startingNote));
	
	return 0;
}