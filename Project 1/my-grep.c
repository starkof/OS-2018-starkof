// Simple implementation the grep command in Unix systems
// This program prints the lines in a file that match a given search string
// by: Stephan N. Ofosuhene

#include <stdio.h>

#define BUFFER_SIZE 1028

int chlength(char *arr){
	// abstraction for finding the length of a character array
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
	// check if the right number of parameters have been provided
	if (argc < 3){
		printf("Please provide a search string and at least 1 filename as parameters\n");
		return 0;
	}
	else if (argc >= 3) {
        FILE *fp;
        char buffer[BUFFER_SIZE];

        for (int i = 2; i <= argc-1; i++){
            char *filename = argv[i];
            printf("\n********* File %d: %s *********\n\n", i-1, filename);
            // open the file
            fp = fopen(filename, "r");

            // check if file was opened successfully
            if (fp == NULL) {
                printf("Cannot open file\n");
                return -1;
            }

            char c;
            char *searchString = argv[1];
            int argSize = chlength(searchString);
            int n = 0;


            // read one line of the file at a time
            while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
                int i = 0;
                // loop through the characters in each line
                while (buffer[i] != '\0') {
                    c = buffer[i];
                    // if a character in the file matches a character in the searcht string
                    if (c == searchString[n]) {
                        // move to the next character in the search string and keep checking
                        n++;
                        argSize--;
                    } else {
                        // go back to the beginning of the search string if a mismatch is found
                        n = 0;
                        argSize = chlength(searchString);
                    }
                    if (argSize == 0) {
                        // print the line if all the characters in the search string match a substring in the line
                        printf("%s", buffer);

                        // go back to the beginning of the search string and keep searching for more matches
                        n = 0;
                        argSize = chlength(searchString);
                    }
                    i++;
                }
            }
            // close the file
            fclose(fp);
        }
	} else {
		printf("Too many arguments have been provided to this program\n");
	}
	return 0;
}
