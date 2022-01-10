#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#define MSG_FILE "/etc/passwd"
#define MAX_SIZE 1000
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
	pthread_t t1,t2;
	int red = 1;
	int blue = 2;
	pthread_create(&t1,NULL,sender,&red);
	pthread_create(&t2,NULL,receiver,&blue);
	pthread_join(t1);
	pthread_join(t2);
	return 0;
}
void *sender(int addr){
	struct msg_form msg;
	for(;;){
		msg.mtype = addr;
		//write
		
		while(1)
		{
			scanf("%s",msg.mtext);
			msgsnd(msqid,&msg,sizeof(msg),0);
			if(strcmp(msg.mtext,"exit") == 0)
			{
				pthread_cancel(treceiver);
			        pthread_exit(NULL);
			}
		}
	}
}
void *receiver(int addr){
	struct msg_form msg;
	for(;;){
		while(1)
		{
			msgrcv(msqid,&msg,sizeof(msg.mtext),addr,0);
			printf("receive message = %s\n",msg.mtext);
			//write
		  	if(strcmp(msg.mtext,"exit") == 0)
                 	{
                                pthread_cancel(treceiver);
                                pthread_exit(NULL);
                  	 }
		{
	}
}
