#include <stdio.h>
#include <string.h>

int getName(char *msg, char *name, int nameSize);

int main(int argc, char *argv[]) {
	const int strLength = 20;
	char firstName[strLength] = {0}, lastName[strLength] = {0}, fullName[2*strLength + 1] = {0};
	
	if(getName("Enter your first name: ", firstName, strLength) != 0 ||
		getName("Enter your last name: ", lastName, strLength) != 0) {
		printf("Invalid input.\n");
		return 1;
	}
	
	strcpy(fullName, firstName);
	char *ptr = strchr(fullName, '\0');
	*ptr = ' ';
	*(ptr+1) = '\0';
	strcat(fullName, lastName);
	
	if(strcmp(fullName, "Olly Seber") == 0) {
		printf("HELLO, SIR! Please, come on in and sit down.\n\tA massage? Certainly, sir!\n");
		printf("Press RETURN key to continue...\n");
		getchar();
	}
	
	printf("%s\n", fullName);
	
	return 0;
}

int getName(char *msg, char *name, int nameSize) {
	char tempName[nameSize];
	printf("%s", msg);
	if(fgets(tempName, nameSize, stdin) == NULL)
		return 1;
	if(strchr(tempName, '\n') == NULL)
		return 2;
	*strchr(tempName, '\n') = '\0';
	strcpy(name, tempName);
	return 0;
}