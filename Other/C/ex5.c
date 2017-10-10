#include <stdio.h>

int main(int argc, char** argv)
{
	int distance = -97;
	float power = 2.545f;
	double super_power = 243242.234234;
	char initial = 'A';
	char first_name[] = "Zed";
	char last_name[] = "Shaw";
	
	printf("You are %u miles away.\n", distance);
	printf("You have %e levels of power.\n", power);
	printf("You have %f awesome super powers.\n", super_power);
	printf("I have an initial %c.\n", initial);
	printf("I have a first name %s.\n", first_name);
	printf("I have a last name %s.\n", last_name);
	printf("My whole name is %s %c. %s.\n", first_name, initial, last_name);
	printf("");
	
	return 0;
}