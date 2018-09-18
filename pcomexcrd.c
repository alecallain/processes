#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <signal.h>

// static void pSigHandler(int signo){
//     switch (signo) {
//             case SIGTSTP:
//             printf("TSTP");
//             fflush(stdout);
//             break;
//     }
// }
//
// int main(void)
// {
//     struct sigaction psa;
//     psa.sa_handler = pSigHandler;
//     sigaction(SIGTSTP, &psa, NULL);
//     for(;;) {}
//     return 0;
// }

void sigusr1Handler (int sigNum);
void sigusr2Handler (int sigNum);
void sigintHandler (int sigNum);

int main(int argc, char*argv[]){
	int status, pid;
	// Make fork
	// signal(SIGUSR1, sigusr1Handler);
	// signal(SIGUSR2, sigusr2Handler);
	// signal(SIGINT, sigintHandler);
  struct sigaction sigs1;
  sigs1.sa_handler = sigusr1Handler;
  sigaction(SIGUSR1, &sigs1, NULL);
  struct sigaction sigs2;
  sigs2.sa_handler = sigusr2Handler;
  sigaction(SIGUSR2, &sigs2, NULL);
  struct sigaction sigint;
  sigint.sa_handler = sigintHandler;
  sigaction(SIGINT, &sigint, NULL);

	pid = fork(); //fork returns the child pid
  pid1 = fork();
	// seed random with a random number
	srand(rand());
	if(pid < 0 || pid1 < 0){
		// Fork failed
		perror("Fork failed\n");
		exit(1);
	}
	else if (!pid || !pid1){ // child
		//wait a random amount of time between 1 and 5 seconds
		while(1){
			sleep((rand()%5)+1);
			// trigger a signal to send to the parent
			rand() % 2 > 0 ? kill(getppid(), SIGUSR2): kill(getppid(), SIGUSR1);
		}
	}
	else { //parent
		printf("Spawned child process, id, %d\nwaiting...\t", pid);
		waitpid(pid, &status, 0);
		//exit(0);
	}

}
//install siguser1
void sigusr1Handler (int sigNum){
	//signal(sigNum, SIG_IGN); // if we area already handeling the signal then we dont want to handle it if it triggers again while were handling it
	printf("received a SIGUSR1 signal\nwaiting...\t");
	fflush(stdout);
}
//install sigusr2
void sigusr2Handler (int sigNum){
	//signal(sigNum, SIG_IGN);
	printf("received a SIGUSR2 signal\nwaiting...\t");
	fflush(stdout);
}
void sigintHandler (int sigNum){
	//signal(sigNum, SIG_IGN);
	puts("^C Recived, Shutting Down...\n");
	exit(0);
}
