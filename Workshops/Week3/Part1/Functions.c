#include <stdio.h>
#include <math.h>

#define REFERENCE_FREQUENCY 440.0

double frequencyToMidi(double frequency);

int main(void)
{
	char userInputBuffer[40] = {0};
	double frequency = 0, noteNumber = 0;
	
	printf("Enter a frequency to be converted ");
	if(fgets(userInputBuffer, sizeof userInputBuffer, stdin) != NULL) {
		if(sscanf(userInputBuffer, "%lf", &frequency) != 1) {
			printf("Input not recognised!\n");
			return(1);
		}
		if(frequency <= 0) {
			printf("Input out of range!\n");
			return(2);
		}
	}
	
	noteNumber = frequencyToMidi(frequency);	
	
	printf("The Midi note number equivalent is %f\n", noteNumber);
	
	return 0;
}

double frequencyToMidi(double frequency)
{
	return (12*log(frequency / REFERENCE_FREQUENCY) / log(2)) + 57;
}