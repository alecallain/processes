#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <signal.h>

void sigusr1Handler (int sigNum);
void sigusr2Handler (int sigNum);
void sigintHandler (int sigNum);

int main(int argc, char*argv[]){

	int status, pid;
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
		while(1){

			// Child process is created
			//wait a random amount of time between 1 and 5 seconds
			sleep((rand()%5)+1);
			// trigger a signal to send to the parent
			//printf("child process: %d\n", pid);
			puts("wating...\t")
			rand() % 1 > 0 ? kill(getppid(), SIGUSR2): kill(getppid(), SIGUSR2);
	  }
	}
	else { //parent
		// Command is executed
		waitpid(pid, &status, 0);
		signal(SIGUSR1, sigusr1Handler);
		signal(SIGUSR2, sigusr2Handler);
		signal(SIGINT, sigintHandler);
		//exit(0);
	}

}
//install siguser1
void sigusr1Handler (int sigNum){
	//signal(sigNum, SIG_IGN); // if we area already handeling the signal then we dont want to handle it if it triggers again while were handling it
	puts("received a SIGUSR1 signal\n");
}
//install sigusr2
void sigusr2Handler (int sigNum){
	//signal(sigNum, SIG_IGN);
	puts("received a SIGUSR2 signal\n");
}
void sigintHandler (int sigNum){
	//signal(sigNum, SIG_IGN);
	puts("^C Recived, Shutting Down...");
	exit(0);
}
