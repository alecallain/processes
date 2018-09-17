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

int main(int argc, char*argv[]){

	int status, cpid;
	// Make fork
	cpid = fork(); //fork returns the child pid
	// seed random with a random number
	srand(rand());
	if(cpid < 0){
		// Fork failed
		perror("Fork failed\n");
		exit(1);
	}
	else if (cpid){ // child
		// Child process is created
		waitpid(cpid, &status, 0);
		//wait a random amount of time between 1 and 5 seconds
		sleep((rand()%5)+1);
		// trigger a signal to send to the parent

		rand() % 1 > 0 ? /*puts("2"): puts("1");//*/ kill(getppid(), SIGUSR2): kill(getppid(), SIGUSR2);
		puts("child process: %s", cpid);
	}
	else { //parent
		// Command is executed
		puts("This is the parent: %s", getppid());
		signal(SIGUSR1, sigusr1Handler);
		signal(SIGUSR2, sigusr2Handler);
		puts("parent process");
		exit(0);
	}

}
//install siguser1
void sigusr1Handler (int sigNum){
	//signal(sigNum, SIG_IGN); // if we area already handeling the signal then we dont want to handle it if it triggers again while were handling it
	puts("Signal 1 uesd?\n");
}
//install sigusr2
void sigusr2Handler (int sigNum){
	//signal(sigNum, SIG_IGN);
	puts("Signal 1 uesd?\n");
}
