#include <stdio.h>
#include <time.h>
void wait(int s){
	clock_t end_wait;
	end_wait=clock()+s * CLOCKS_PER_SEC;
	while(clock()<end_wait){}
}
int main(){
	int input;
	printf("How long do you want to wait? \n");
	scanf("%d", &input);
	wait(input);
	printf("%d seconds have passed.", input);
	return 0;
}
