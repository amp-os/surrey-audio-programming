#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define REFERENCE_FREQUENCY 440.0

double g_reference = 440;

double frequencyToMidi(double frequency);
void printComparison(double frequency1, double frequency2);
double closest(double target, double contestant1, double contestant2);

int main(int argc, char *argv[])
{
	double frequency1 = 0, frequency2 = 0;
	
	if(argc != 3 && argc != 4) {
		printf("Error: you must enter two or three integer arguments\n");
		return(4);
	}
	
	frequency1 = atof(argv[1]);
	frequency2 = atof(argv[2]);
	
	if(argc == 4) {
	g_reference = atof(argv[3]);
	#undef REFERENCE_FREQUENCY
	#define REFERENCE_FREQUENCY g_reference
	
	
	}
	
	if(frequency1 <= 0 || frequency2 <= 0) {
		printf("Input error\n");
		return(5);
	}
	
	printf("%f is closer to %fHz\n", closest(REFERENCE_FREQUENCY, frequency1, frequency2), REFERENCE_FREQUENCY);
		
	printComparison(frequency1, frequency2);
	
	char userInputBuffer[40] = {0};
	
	printf("Enter a frequency to be converted ");
	if(fgets(userInputBuffer, sizeof userInputBuffer, stdin) != NULL) {
		if(sscanf(userInputBuffer, "%lf", &frequency1) != 1) {
			printf("Input not recognised!\n");
			return(1);
		}
		if(frequency1 <= 0) {
			printf("Input out of range!\n");
			return(2);
		}
	}	
	
	printf("The Midi note number equivalent is %f\n", frequencyToMidi(frequency1));
	
	printf("Enter two frequencies to be compared ");
	if(fgets(userInputBuffer, sizeof userInputBuffer, stdin) != NULL) {
		if(sscanf(userInputBuffer, "%lf %lf", &frequency1, &frequency2) != 2) {
			printf("Input not recognised!\n");
			return(1);
		}
		if(frequency1 <= 0 || frequency2 <= 0) {
			printf("Input out of range!\n");
			return(2);
		}
	}
	
	printComparison(frequency1, frequency2);
	
	return 0;
}

double frequencyToMidi(double frequency)
{
	return (12*log(frequency / REFERENCE_FREQUENCY) / log(2)) + 57;
}

void printComparison(double frequency1, double frequency2)
{
	printf("The first note is %f semitones higher than the second\n", frequencyToMidi(frequency1) - frequencyToMidi(frequency2));
}

double closest(double target, double contestant1, double contestant2)
{
	return fabs(target - contestant1) <= fabs(target - contestant2) ? contestant1 : contestant2;
}