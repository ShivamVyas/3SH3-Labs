#include  <stdio.h> 
#include  <stdlib.h>
#include  <string.h>
#include  <unistd.h>
#include  <sys/types.h>

int  main(void) {
	int 	cfd[2], pfd[2]; //pipes
	char 	writebuffer[100];
	char 	readbuffer[100];
	pid_t 	pid;

	int 	temp = 0;
	int 	sum = 0; //for the sum

	pipe(cfd); //pipes
	pipe(pfd);

	pid = fork(); //fork

	if (pid == 0) { //Child
		close(cfd[0]); //close non needd (child side read, parent side write)
		close(pfd[1]);

		while (1) {
			scanf("%s", writebuffer); //get an input
			write(cfd[1], writebuffer, sizeof(writebuffer)); //send the input
			if (!strcmp(writebuffer, "-1")) break;//break when -1
		}

		read(pfd[0], readbuffer, sizeof(readbuffer)); //read from the parent
		printf("Received Sum: %s\n", readbuffer); //print received number

	}
	else { //Parent
		close(cfd[1]); //close non needed (child side write, parent side read)
		close(pfd[0]);

		while (1) {
			read(cfd[0], readbuffer, sizeof(readbuffer)); //read from the child

			if (!strcmp(readbuffer, "-1")) break;//check if its -1

			sscanf(readbuffer, "%i", &temp); //if no -1, add to the sum
			sum += temp;
		}

		sprintf(writebuffer, "%i", sum); //write the sum to the writebuffer
		write(pfd[1], writebuffer, sizeof(writebuffer)); //write to the child
	}
	return  0; //exit
}