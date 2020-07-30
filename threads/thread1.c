#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void* myturn(void* arg){
	for(int i=0; i<8; i++){
		sleep(1);
		printf("My turn %d\n", i);
	}
	return NULL;
}
void yourturn(){
	for(int i=0; i<3; i++){
		sleep(1);
		printf("Your turn %d\n", i);
	}
}
int main(){
	pthread_t newthread;
	pthread_create(&newthread, NULL, myturn, NULL);
	yourturn();
	//wait until newthread completes
	pthread_join(newthread, NULL);
	puts("thread's done!");
	return 0;
}
