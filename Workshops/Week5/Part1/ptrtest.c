#include <stdio.h>
#include <stdlib.h>

typedef struct s {
	int a;
	double b;
	} thing;

void setThingA(thing *ptr, int value) {
	ptr->a = value;
}

void modifyMe(int *ptr) {
	*ptr = 10;
}

int main(void) {
	int x = 0;
	int *ptr = &x;
	
	
	modifyMe(ptr);
	
	printf("%d\n", x);
	
	thing *aThing;
	
	aThing = malloc(sizeof(thing));
	
	aThing->a = 0;
	
	printf("%d\n", aThing->a);
	
	setThingA(aThing, 10);
	
	printf("%d\n", aThing->a);
	
	
	return 0;
}