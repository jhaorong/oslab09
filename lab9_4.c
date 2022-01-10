#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <pthread.h>
#define MSG_FILE "/etc/passwd"
#define MAX_SIZE 1000
void *receiver(int);
void *sender(int);
struct msg_form{
	long mtype;
	char mtext[MAX_SIZE];
};
int msqid;
pthread_t tsender,treceiver;
int main()
{
	key_t key;
	struct msg_form msg;
	if((key = ftok(MSG_FILE,'z')) < 0){
		perror("ftok error");
		exit(1);
	}
	if((msqid = msgget(key,IPC_CREAT|0777)) == -1){
		perror("msgget error");
		exit(1);
	}
	//thread seting
	int red = 8;
	int blue = 7;
	pthread_create(&tsender,NULL,sender,8);
	pthread_create(&treceiver,NULL,receiver,7);
	pthread_join(tsender,NULL);
	pthread_join(treceiver,NULL);
	return 0;
}
void *sender(int addr){
	struct msg_form msg;
	for(;;){
		msg.mtype = addr;
		//write
		printf("<Enter text>\n");
		fgets(msg.mtext, MAX_SIZE, stdin);
		msgsnd(msqid,&msg,sizeof(msg.mtext),0);
		if(strcmp(msg.mtext,"exit\n") == 0)
		{
			pthread_cancel(treceiver);
			pthread_exit(NULL);
		}
		
	}
}
void *receiver(int addr){
	struct msg_form msg;
		for(;;)
		{
			msgrcv(msqid,&msg,sizeof(msg.mtext),addr,0);
			printf("receive message = %s\n",msg.mtext);
			//write
		  	if(strcmp(msg.mtext,"exit\n") == 0)
                 	{
                                pthread_cancel(tsender);
                                pthread_exit(NULL);
                  	 }
		
		}
}
