#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int count = 0;
void *PrintCount(void *arg)
{
	int i=0;
	for(i=0;i<(*(int*)arg);i++)
	{
		//printf("Thread ID is:%lu,",pthread_self());
		//printf("num is %d\n",count);
		count++;
	}
	printf("Thread ID is:%lu Completed. count = %d\n",pthread_self(),count);
	pthread_exit(NULL);
}
int main()
{
	int iter = 25000000;
	pthread_t thread1,thread2,thread3,thread4;
	pthread_create(&thread1,NULL,PrintCount,&iter);
	pthread_create(&thread2,NULL,PrintCount,&iter);
	pthread_create(&thread3,NULL,PrintCount,&iter);
	pthread_create(&thread4,NULL,PrintCount,&iter);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);
	pthread_join(thread4,NULL);
	printf("the count value is:%d\n",count);
	return 0;
	
}
