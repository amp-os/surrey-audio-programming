#include <stdio.h>

int main(int argc, char *argv[])
{	
	char str[] = "This is a string";
	// T h i s   i s   a ... \0   <- these are characters
	// 1 2 3 4 5 6 7 8 9 ...  x   <- these are the "addresses"
	// 0 1 2 3 4 5 6 7 8 ...  n   <- index of array
	
	// str[0] = 'T'
	// str[1] = 'h'
	// str[n] = '\0'
	
	char *str2 = "This is also a string";
	// pointer str2 points to address 1.
	// address 1 contains "T" character of "This is also a string"
	// * means dereference. Just str on its own is pointing to some memory. Dereferencing
	// this means you are looking at the data stored in this memory.
	// *str2 = "This ...\0"
	// When the compiler is given either str[] or *str, it just reads sequential memory 
	// until it sees the '\0'.
	
	
}