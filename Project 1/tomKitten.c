// Simple implementation of the cat command in unix systems
// The name of this program is inspired by The Tale of Tom Kitten and wordplay on cat
// by: Stephan N. Ofosuhene

#include <stdio.h>

#define BUFFER_SIZE 255


int main(int argc, char *argv[]){
	if (argc == 1){
		printf("Please provide the name of a file as a parameter \n");
		return 0;
	} else if (argc == 2){
		FILE *fp;
		char buffer[BUFFER_SIZE];

		fp = fopen(argv[1], "r");
		if (fp == NULL){
			printf("Cannot open file\n");
			return -1;
		}

		while (fgets(buffer, BUFFER_SIZE, fp) != NULL){
			printf("%s", buffer);
		}
		fclose(fp);
	}
	return 0;
}
