#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
int X=0;
int N=100;

void* increm(){
	int i;
	for(i=0;i<N;i++) X+=1;	
}


int main(){
	int i;
	void* (*x)()=increm;
	pthread_t thrd[100];
	
	for(i=0;i<N;i++){
	pthread_create(&thrd[i], NULL, x, NULL);
	}
	pthread_join(thrd[i],NULL);
	printf("%d",X);	
return 0;
}
