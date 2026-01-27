#include "./common/head.h"
#include "wechat.h"

struct Msg *share_memory = NULL;

int main(){
	key_t key = ftok(".",8888);
	
	int shmid;
	if((shmid = shmget(key,sizeof(struct Msg), IPC_CREAT | 0666)) < 0){
		perror("shmget()");
		exit(1);
	}

	if((share_memory = (struct Msg*)shmat(shmid,NULL,0)) == NULL){
		perror("shmat()");
		exit(1);
	}

	//初始化操作
	//清空共享内存
	memset(share_memory,0,sizeof(struct Msg));
	//初始化共享锁
	pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutexattr_setpshared(&mutex_attr,PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&share_memory->mutex,&mutex_attr);
	//初始化信号量
    pthread_condattr_t cond_attr;
    pthread_condattr_init(&cond_attr);
    pthread_condattr_setpshared(&cond_attr,PTHREAD_PROCESS_SHARED);
    pthread_cond_init(&share_memory->cond,&cond_attr);

	while(1){
		pthread_mutex_lock(&share_memory->mutex);
		DBG(RED"Server Got mutex!\n"NONE);
		while (!strlen(share_memory->msg)){
			pthread_cond_wait(&share_memory->cond,&share_memory->mutex);
		}
		DBG(RED"Server Got a cond signal!\n"NONE);		

		printf(GREEN"<%s> : "YELLOW"%s\n",share_memory->name,share_memory->msg);
		memset(share_memory->msg,0,sizeof(share_memory->msg));

		pthread_mutex_unlock(&share_memory->mutex);
	}

	return 0;
}


