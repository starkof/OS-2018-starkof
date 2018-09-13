// Simple implementation the grep command in Unix systems
// This program prints the lines in a file that match a given search string
// by: Stephan N. Ofosuhene

#include <stdio.h>

#define BUFFER_SIZE 255

int chlength(char *arr){
	int n = 1;
	for (int i = 1; i < 1000; i++){
		if (arr[i] == '\0'){
			break;
		}
		n++;
	}
	return n;
}

int main(int argc, char *argv[]){
	if (argc == 1){
		printf("Please provide a search string and a file name\n");
		return 0;
	} else if (argc == 2){
		printf("Please provide a search string and a file name\n");
		return 0;
	}
	else if (argc == 3){
		FILE *fp;
		char buffer[BUFFER_SIZE];

		fp = fopen(argv[2], "r");
		if (fp == NULL){
			printf("Cannot open file\n");
			return -1;
		}
		char c;
		char *searchString = argv[1];
		int argSize = chlength(searchString);
		int n = 0;
		while (fgets(buffer, BUFFER_SIZE, fp) != NULL){
			int i = 0;
			while (buffer[i] != '\0'){
				c = buffer[i];
				if (c == searchString[n]){
					n++;
					argSize--;
				} else {
					n = 0;
					argSize = chlength(searchString);
				}
				if (argSize == 0){
					printf("%s", buffer);
					n = 0;
					argSize = chlength(searchString);
				}
				i++;
			}
		}
		fclose(fp);
	}
	return 0;
}
