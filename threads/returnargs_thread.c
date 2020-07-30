#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
void* myturn(void* arg){
	int* intptr = (int *)malloc(sizeof(int));
	*intptr = 5;
	for(int i=0; i<8; i++){
		sleep(1);
		printf("My turn %d %d\n", i, *intptr);
		(*intptr)++;
	}
	return intptr;
}
void yourturn(){
	for(int i=0; i<4; i++){
		sleep(2);
		printf("Your turn %d\n", i);
	}
}
int main(){
	pthread_t newthread;
	int *result;
	pthread_create(&newthread, NULL, myturn, NULL);
	yourturn();
	//wait until newthread completes
	pthread_join(newthread, (void *)&result);
	printf("thread's done! v=%d\n", *result);
	return 0;
}
