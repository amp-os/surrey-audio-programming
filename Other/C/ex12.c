#include <stdio.h>
#include <ctype.h>
#include <string.h>

void printLetters(char *array, unsigned long arrayLength)
{
	for(int i = 0; i < arrayLength; ++i){
		if(isalpha(array[i]) || isblank(array[i]))
			printf("%c", array[i]);
	}
	printf("\n");
}

void printArguments(int argc, char **argv)
{
	for(int i = 1; i < argc; ++i)
		printLetters(argv[i], strlen(argv[i]));
}

int main(int argc, char *argv[])
{
	printArguments(argc, argv);
	return 0;
}