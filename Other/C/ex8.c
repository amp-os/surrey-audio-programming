#include <stdio.h>

int main(int argc, char** argv)
{
	char *name = "Hel";
	printf("%s\n", name);
	
	printf("%d\n", name);
	name[1] = '\0';
	printf("%s\n", name);
	
	return 0;
}