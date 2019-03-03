#include <stdio.h>
#include <time.h>
int main(){
	time_t s;
	s=time(NULL);
	printf("Number of hours since Jan 1, 1970 is %ld \n", s/3600);
	printf("Today is %s", ctime(&s));
	return 0;
}
