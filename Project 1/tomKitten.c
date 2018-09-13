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

		// open the file
		fp = fopen(argv[1], "r");

		// check if the file was opened successfully
		if (fp == NULL){
			printf("Cannot open file\n");
			return -1;
		}

		// read the file one line at a time
		while (fgets(buffer, BUFFER_SIZE, fp) != NULL){
			// print each line in the file
			printf("%s", buffer);
		}
		// close the file
		fclose(fp);
	} else {
		printf("Too many arguments have been provided for this program\n");
	}
	return 0;
}
