#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void* myturn(void* arg){
	for(int i=0; i<8; i++){
		sleep(1);
		printf("My turn %d", i);
	}
}
void yourturn(){
	for(int i=0; i<3; i++){
	
int main(){
	return 0;
}
