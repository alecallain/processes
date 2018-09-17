#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

int main(int argc, char*argv[]){

	int status, pid;
	//struct rusage usage;
	// Make fork
	pid = fork();
	if(pid < 0){
		// Fork failed
		perror("Fork failed\n");
		exit(1);
	}
	else if (pid){ // child
		// Child process is created
		waitpid(pid, &status, 0);
		puts("child process");
	}
	else { //parent
		// Command is executed
		signal(SIGUSR1, sigusr1Handler);
		signal(SIGUSR2, sigusr2Handler);
		puts("parent process");
		exit(0);
	}

}
void sigusr1Handler (int sigNum){
	puts("Signal 1 uesd?\n");
}

void sigusr2Handler (int sigNum){
	puts("Signal 1 uesd?\n");
}
