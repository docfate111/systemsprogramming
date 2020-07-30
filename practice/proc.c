#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/types.h>
//pid_t getpid(void); gets process ID
//pid_t getppid(void); gets parent process ID
//int getpriority(int which, int who[, int prio]);
//default 0, +20->slower, -20->faster
//pid_t fork(void) starts child process
//pid_t wait(int *status)
//pid_t waitpid(pid_T pid, int *status, int options)
int main(){
	printf("The program's process ID is %d\n", getpid());
	printf("The program's process ID is %d\n", getppid());
	printf("The priority is: %d\n", getpriority(PRIO_PROCESS, getpid()));
	int childpid=fork();
	//both processes run at the same time
	if(childpid!=0){
		printf("%d is the parent process\n", childpid);
		int status=0;
		//parent wait for child
		int c=wait(&status);
		if(c==-1){printf("Error]n");}
		else{printf("Child terminated");}
	}else{
		printf("%d is the child process\n", childpid);
		exit(0);
	}
	return 0;
}
