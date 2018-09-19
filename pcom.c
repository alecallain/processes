#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <signal.h>

/**
 * Sends signals between process at random intervals
 * overwrites SIGINT and creates SIGUSR2 and SIGUSR1
 *
 * @author Allison Bolen
 * @author Alec Allain
 * @version 9/20/18
 */

 /** Insanciate the handlers */
void sigusr1Handler (int sigNum);
void sigusr2Handler (int sigNum);
void sigintHandlerParent (int sigNum);
void sigintHandlerChild (int sigNum);
/** Main function */
int main(int argc, char*argv[]){
	int status, pid;
	// install the signals
	signal(SIGUSR1, sigusr1Handler);
	signal(SIGUSR2, sigusr2Handler);
	signal(SIGINT, sigintHandlerParent);
	// Make fork
	pid = fork(); //fork returns the child pid
	// seed random with a random number
	srand(rand());
	if(pid < 0){
		// Fork failed
		perror("Fork failed\n");
		exit(1);
	}
	else if (!pid){ // child
		// loop until SIGINT is triggered
		signal(SIGINT, sigintHandlerChild);
		while(1){
			//wait a random amount of time between 1 and 5 seconds
			sleep((rand()%5)+1);
			// trigger a signal to send to the parent
			rand() % 2 > 0 ? kill(getppid(), SIGUSR2): kill(getppid(), SIGUSR1);
		}
	}
	else { //parent
		printf("Spawned child process, id, %d\nwaiting...\t", pid);
		waitpid(pid, &status, 0);
	}
}
/** Signal handler for SIGUSR1 */
void sigusr1Handler (int sigNum){
	printf("received a SIGUSR1 signal\nwaiting...\t");
	fflush(stdout);
}
/**Signal handeler for SIGUSR2 */
void sigusr2Handler (int sigNum){
	printf("received a SIGUSR2 signal\nwaiting...\t");
	fflush(stdout);
}
/** Signal overwrite for SIGINT */
void sigintHandlerParent (int sigNum){
	puts("^C Recived, Shutting Down...\n");
	exit(0);
}
/** Signal overwrite for SIGINT */
void sigintHandlerChild (int sigNum){
	exit(0);
}
