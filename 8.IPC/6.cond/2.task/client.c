#include "./common/head.h"
#include "wechat.h"

struct Msg *share_memory = NULL;

int main(int argc,char **argv){
	int opt;
	char name[20] = {20};
	while((opt = getopt(argc,argv,"n:")) != -1){
		switch(opt){
			case 'n':	
				strcpy(name,optarg);
				break;
			default:
				fprintf(stderr,"Usage : %s -n name.\n",argv[0]);
				exit(1);
		}	
	}
	
	int shmid;
	key_t key = ftok(".",8888);
	if((shmid = shmget(key,sizeof(struct Msg),IPC_CREAT | 0666)) < 0){
		perror("shmget()");
		exit(1);
	}	

	share_memory = shmat(shmid,NULL,0);
	
	while(1){
		char msg[1024] = {0};
		//读取一行字符串,直到遇到换行符
		scanf("%[^\n]",msg);
		//读取换行符
		getchar();
		//读取信息为空则跳过
		if(!strlen(msg)){
			continue;
		}
		while(1){
			//共享内存是有信息的,服务端还没处理完,客户端等待
			//如果没信息,获取锁,停止等待
			if(!strlen(share_memory->msg)){
				pthread_mutex_lock(&share_memory->mutex);
				break;
			}
		}
		strcpy(share_memory->name,name);
		strcpy(share_memory->msg,msg);
		pthread_cond_signal(&share_memory->cond);
		pthread_mutex_unlock(&share_memory->mutex);
	}

	return 0;
}

