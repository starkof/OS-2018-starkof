// Simple implementation of the cat command in unix systems
// The name of this program is inspired by The Tale of Tom Kitten and wordplay on cat
// by: Stephan N. Ofosuhene

#include <stdio.h>


int main(int argc, char *argv[]){
	if (argc == 1){
		printf("Please provide the name of a file as a parameter \n");
		return 0;
	} else if (argc >= 2) {
        FILE *fp;

        for (int i = 1; i <= argc - 1; i++) {
            // open the file
            char *filename = argv[i];
            printf("\n********* File %d: %s *********\n\n", i, filename);
            fp = fopen(filename, "r");

            // check if the file was opened successfully
            if (fp == NULL) {
                printf("Cannot open file\n");
                return -1;
            }

            char c;
            do {
                c = fgetc(fp);
                printf("%c", c);
            } while (c != EOF);

            fclose(fp);
        }
    }
	return 0;
}
