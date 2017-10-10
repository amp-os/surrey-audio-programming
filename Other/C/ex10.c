#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = argc;
	while(--i > 0)
		printf("arg %d: %s\n", i, argv[i]);
	
	char *places[] = {"Here", "asdfad", "Anywhere", "On a train"};
	
	int num_places = 4;
	i=-1;
	
	while(++i <num_places)
		places[i]=argv[i+1];
	
	for(int i = 0; i < num_places; ++i)
		printf("place %d: %s\n", i, places[i]);
	
	return 0;
}