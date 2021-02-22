#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void alarm_handler ( int signo ) {
    if (signo == SIGALRM){
        printf ("Alarm\n") ; 
    }
}

void sigint_handler(int signo){
    printf("CTRL+C Pressed\n");
}

void sigtstp_handler( int signo){
    if (signo == SIGTSTP)
    {
        printf ("CTRL+Z Pressed\n");
        exit(1); 
    }
}

int main (void) {
    unsigned int alarm(unsigned int seconds);

    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigint2_handler); //stops the process

    if (signal(SIGALRM, alarm_handler) == SIG_ERR || signal(SIGINT, sigint_handler) == SIG_ERR || signal(SIGTSTP,sigtstp_handler) == SIG_ERR) {
        printf ("Failed to register alarm handler") ;
        exit (1) ;
    }

    while (1) { 
        signal(SIGALRM, alarm_handler);

        alarm(2);

        sleep(10)
    } 
}
