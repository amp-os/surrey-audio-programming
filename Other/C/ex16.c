#include <stdio.h> // For in and out
#include <assert.h> // For checking for NULL memory locations
#include <stdlib.h> // For malloc and free
#include <string.h> // For duplicating a string

struct Person { // Data structure called struct with four members
	char *name;
	int age;
	int height;
	int weight;
};

struct Person* Person_create( char *name, int age, int height, int weight ) { // Struct creator, returns pointer
	struct Person *who = malloc( sizeof( struct Person ) ); // Dynamically allocate memory for struct
	assert( who != NULL ); // Check memory allocation
	
	who->name = strdup( name ); // Populate members, duplicating string so allocated dynamically
	who->age = age;
	who->height = height;
	who->weight = weight;
	
	return who; // Return pointer to person
}

void Person_destroy( struct Person *who ) { // For freeing memory dynamically allocated during creation
	assert( who != NULL );
	
	free( who-> name );
	free( who );
}

void Person_print( struct Person *who ) { // Print members of the struct
	printf( "Name: %s\n", who->name );
	printf( "\tAge: %d\n", who->age );
	printf( "\tHeight: %d\n", who->height );
	printf( "\tWeight: %d\n", who->weight );
}

int main( int argc, char *argv[] ) {
	
	/* Make two people */
	struct Person *joe = Person_create( "Joe Alex", 32, 64, 140 );
	struct Person *frank = Person_create( "Frank Blank", 20, 72, 180 );
	
	/* Print the people */
	printf( "Joe is at memory location %p:\n", joe );
	Person_print( joe );
	
	printf( "Frank is at memory location %p:\n", frank );
	Person_print( frank );
	
	/* Make everyone age 20 years */
	joe->age += 20;
	joe->height -= 2;
	joe->weight += 40;
	Person_print( joe );
	
	frank->age += 20;
	frank->weight += 20;
	Person_print(frank);
	
	/* Destroy the people */
	Person_destroy( joe );
	Person_destroy( frank );
	
	return 0;
}
