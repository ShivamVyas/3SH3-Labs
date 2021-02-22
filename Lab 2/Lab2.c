#include  <stdio.h> 
#include  <stdlib.h>
#include  <string.h>
#include  <unistd.h>
#include  <sys/types.h>

int  main(void) {
	int 	cfd[2], pfd[2]; //pipes
	int 	temp = 0;
	int 	sum = 0;
	
	char 	writebuffer[100], readbuffer[100]; //buffers
	
	pid_t 	pid = fork();
	pipe(cfd); //pipes
	pipe(pfd);
 

	if (pid == 0) { //Child
		close(cfd[0]); 
		close(pfd[1]);

		while (true){
			scanf("%s", writebuffer); //get an input
			write(cfd[1], writebuffer, sizeof(writebuffer)); //send the input
			if (!strcmp(writebuffer, "-1")) break;//break when -1
		}

		read(pfd[0], readbuffer, sizeof(readbuffer)); //read from the parent
		printf("Received Sum: %s\n", readbuffer); //print received number

	}
	else { //Parent
		close(cfd[1]); 
		close(pfd[0]);

		while (true) {
			read(cfd[0], readbuffer, sizeof(readbuffer)); //read from the child

			if (!strcmp(readbuffer, "-1")) {
				break;//check if its -1
			}
			sscanf(readbuffer, "%i", &temp); //else, add to the sum
			sum += temp;
		}

		sprintf(writebuffer, "%i", sum); //write the sum to the writebuffer
		write(pfd[1], writebuffer, sizeof(writebuffer)); //write to the child
	}
	return  0;
}