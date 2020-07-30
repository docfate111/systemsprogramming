#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//int fcntl(int fd, int cmd);
//int fcntl(int fd, int cmd, long arg or struct* lock);
//if returns -1 didn't work
//acts on open file fd and performs cmd
int filestatus(int file){
	int val=fcntl(file, F_GETFL);
	if(val==-1){
		return -1;
	}
	printf("File descriptor: %d\n", file);
	switch(val & O_ACCMODE){
		case O_WRONLY: printf("Write only"); break;
		case O_RDONLY: printf("Read only"); break;
		case O_RDWR: printf("Write and read"); break;
		default: printf("Bad mode"); break;
	}
}
int main(int argc, char* argv[]){
	int fd=open(*argv, O_RDONLY);
	if(fd!=-1){
		filestatus(fd);
	}
	return 0;
}
