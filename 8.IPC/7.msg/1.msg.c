#include "./common/head.h"

struct msgbuf{
	long mtype;
	char mtext[256];
};

void send_msg(int qid,long mtype){
	struct msgbuf msg;
	memset(&msg,0,sizeof(msg));
	msg.mtype = mtype;

	//伪信息
	time_t t;
	time(&t);
	char *time_str = ctime(&t);
    //记得替换ctime末尾的\n为\0
    time_str[strcspn(time_str,"\n")] = '\0';
	snprintf(msg.mtext,sizeof(msg.mtext),"A msg at %s",time_str);	

	if(msgsnd(qid,(void*)&msg,sizeof(msg.mtext),IPC_NOWAIT) == -1){
		perror("msgsnd");
		exit(1);
	}
	printf(YELLOW"Msg Sent: [%s].\n"NONE,msg.mtext);
}

void recv_msg(int qid,long mtype){
	struct msgbuf msg;
    if(msgrcv(qid,(void*)&msg,sizeof(msg.mtext),mtype,IPC_NOWAIT | MSG_NOERROR) == -1){
		if(errno != ENOMSG){
			perror("msgrcv()");
			exit(1);
		}
		printf(YELLOW"No message available in msg queue.\n"NONE);
	}else{
		printf(GREEN"Msg recv: [%s].\n"NONE,msg.mtext);
	}
}

int main(int argc,char** argv){
	int opt;
	int mode = 0;	
	long mtype = 1;
	//-s send, -r receive, -t type
	while((opt = getopt(argc,argv,"srt:")) != -1){
		switch(opt){
			case 's':
				mode = 1;
				break;
			case 'r':
                mode = 2;
                break;
			case 't':
                mtype = atoi(optarg);
				if(mtype <= 0){
					fprintf(stderr,"Usage: %s [-s -r -t mytpe].\n",argv[0]);
					exit(1);	
				}
                break;
			default:
				fprintf(stderr,"Usage: %s [-s -r -t mytpe].\n",argv[0]);
                exit(1);
		}
	}

	if(mode == 0){
		fprintf(stderr,"Usage: %s [-s -r -t mytpe].\n",argv[0]);
		fprintf(stderr,"must use either -r or -s option.\n");
        exit(1);
	}

	int msgqid;
	key_t key = ftok(".",9999); 
	if((msgqid = msgget(key, IPC_CREAT | 0666)) == -1){
		perror("msgget()");
		exit(1);
	}

	if(mode == 1){
		send_msg(msgqid,mtype);
	}else{
		recv_msg(msgqid,mtype);
	}

	return 0;
}


