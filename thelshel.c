#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFSIZE 64
#define DELIM " \t\r\n\a"
char *sh_read();
char **sh_split(char* line);
int sh_launch(char **args);
int sh_exec(char **args);
//built-in shell commands
int sh_cd(char **args);
int sh_help(char **args);
int sh_exit(char **args);
char *builtin[]={"cd", "help", "exit"};
int (*builtin_func[]) (char**)={&sh_cd, &sh_help, &sh_exit};
int sh_num(){return sizeof(builtin)/sizeof(char*);}
int main(){
	char* line; char** args; int status;
	 do{
                printf("THEL>");
		//get input and store it in line:
                line=sh_read();
		//divide input into char** array
		args=sh_split(line);
		//execute arguments
		status=sh_exec(args);
        }while(status);
	return 0;
}
char *sh_read(){ //reads input of unlimited size
	char *line=NULL;
	size_t bufsize=0;
	getline(&line, &bufsize, stdin);
	return line;
}
char **sh_split(char* line){//divides input into arguments
	int bufsize=BUFSIZE, position=0;
	char **tokens=malloc(bufsize*sizeof(char*));
	char *token;
	if(!tokens){fprintf(stderr, "tsh: allocation error\n");
		exit(0);}
	token=strtok(line, DELIM);
	//splits string whenever there is a space
	while(token!=NULL){
		tokens[position]=token;
		position++;
		if(position>=bufsize){
			bufsize+=BUFSIZE;
			tokens=realloc(tokens, bufsize*sizeof(char*));
			if(!tokens){fprintf(stderr, "tsh: allocation error\n");
					exit(0);
			}
		}
		token=strtok(NULL, DELIM);
		}
		tokens[position]=NULL;
		return tokens;
}
int sh_launch(char **args){
	pid_t pid, wpid;
	int status;
	pid=fork();
	if(pid==0){//child process begins
		if(execvp(args[0], args)==-1){printf("tsh?");}
		exit(0);
	}else if(pid<0){
		//error
		perror("tsh?");
	}else{//parent process
		do{
			wpid=waitpid(pid, &status, WUNTRACED);
		}while(!WIFEXITED(status)&&!WIFSIGNALED(status));
	}
	return 1;
}
int sh_exec(char** args){
	if(args[0]==NULL){return 1;}//user entered nothing
	for(int i=0; i<sh_num(); i++){
		if(strcmp(args[0], builtin[i])==0){
		//if builtin run builtin function
			return (*builtin_func[i])(args);
		}
	}
	return sh_launch(args);
}
int sh_cd(char **args){
	if(args[1]==NULL){//error if cd is entered without args
		fprintf(stderr, "tsh: expected arg to \"cd\"\n");
	}else{
		if(chdir(args[1])!=0){
			perror("tsh");
		}
	}
	return 1;
}
int sh_help(char **args){
	printf("ThelShel 1.0.0\n");
	printf("Built-in commands are:\n");
	for(int i=0; i<sh_num(); i++){
		printf("%s\n", builtin[i]);
	}
	printf("Use man command for information\n");
}
int sh_exit(char **args){exit(0);}

