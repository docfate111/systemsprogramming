#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void* myturn(void* arg){
	int* intptr = (int *)arg;
	for(int i=0; i<8; i++){
		sleep(1);
		printf("My turn %d %d\n", i, *intptr);
		(*intptr)++;
	}
	return NULL;
}
void yourturn(){
	for(int i=0; i<8; i++){
		sleep(2);
		printf("Your turn %d\n", i);
	}
}
int main(){
	pthread_t newthread;
	//argument:
	int v = 0;
	pthread_create(&newthread, NULL, myturn, &v);
	yourturn();
	//wait until newthread completes
	pthread_join(newthread, NULL);
	printf("thread's done! v=%d\n", v);
	return 0;
}
