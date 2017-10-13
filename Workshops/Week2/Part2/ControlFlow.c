#include <stdio.h>
#include <stdlib.h>

	static const char *g_noteNames[] = {"C", "C#", "D", "D#", "E", "F",
								"F#", "G", "G#", "A", "A#", "B"};
							
	static const int g_majorScale[] = {0, 2, 4, 5, 7, 9, 11};
	static const int g_minorScale[] = {0, 2, 3, 5, 7, 8, 10};

int getInt(char *msg, int *num)
{
	printf("%s", msg);

	if (scanf("%d", num) != 1) {
		printf("Invalid input\n");
		exit(1);
	}

	return *num;
}


int main(int argc, char *argv[])
{
	int startingNote = 0;
	int selectedScale;
	const int *ptrScaleArray;

	getInt("Enter a starting MIDI note number: ", &startingNote);
	
	getInt("Select scale: major (0), or minor (1) ", &selectedScale);
	
	if (selectedScale == 0) {
		ptrScaleArray = g_majorScale;
	}
	else if (selectedScale == 1) {
		ptrScaleArray = g_minorScale;
	}
	else {
		printf("I don't recognise this scale!\n");
		return 2;
	}
	
	for (int scaleIndex = 0; scaleIndex < 8; ++scaleIndex) {
		printf("%s ", g_noteNames[(startingNote + ptrScaleArray[scaleIndex % 7]) % 12]);
	}
	
	printf("\nAre the notes of the %d scale starting on %d\n", selectedScale, startingNote);
	
	return 0;
	
}