#include <unistd.h>
//int execl(const char* path, const char *arg0, ...);
//path is path to executable
//any number of args of strings but last must be NULL
//execv(path, char* args[]);
int main(){
	//int success=execl("/bin/ls", "ls", "-1", NULL);
	char* args[]={"ls", "-1", (char*) 0};
	//null ptr to char
	int id=fork();
	if(id==0){
	//child process
		execv("/bin/ls", args);
	//nothing runs after exec except process
	//(unlike fork)
	}
	//return 0;
}
