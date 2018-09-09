#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]){
	printf("main (pid: %d)\n", (int) getpid());

	int rc = fork();

	if (rc < 0){
		fprintf(stderr, "fork failed\n");
	} else if (rc == 0) {
		printf("Child created (pid: %d)\n", (int) getpid());
	} else {
		printf("Parent of %d (pid: %d)\n", rc, (int) getpid());
	}
	return 0;
}