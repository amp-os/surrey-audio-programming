#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("%d\n", argc);
	if(argc == 1){
		printf("You need to provide at leas one additional argument\n");
		return 1;
		}
	
	for(int a = 1; a < argc; ++a){
	
		for(int i = 0; argv[a][i] != '\0'; ++i){
			char letter = argv[a][i];
			if (letter > 64 && letter < 92)
				letter += 32;
			
			switch(letter){
				case 'a':
				case 'e':
				case 'i':
				case 'o':
				case 'u':
					printf("%d: %c is a vowel\n", i+1, letter);
					break;
				case 'y':
					if(i > 2){
						printf("%d: %c is a vowel\n", i+1, letter);
						break;
						}
				default:
					printf("%d: %c is not a vowel\n", i+1, letter);
				}	
			}
		printf("\n");
		}
	return 0;
}