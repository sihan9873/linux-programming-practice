#include "./common/head.h"
#define THREAD_COUNT 4

//创建多个线程

typedef struct {
	int thread_id;
	const char *msg;
} ThreadArg;

void *thread_start(void* arg){
	ThreadArg *targ = (ThreadArg*)arg;
	printf("Thread %d start, Msg: %s\n",targ->thread_id,targ->msg);
	for(int i = 0;i < 10;i++){
		printf("Thread %d is working. (%d/10)\n",targ->thread_id,i);
		sleep(1);
	}	
	printf("Thread %d finished.\n",targ->thread_id);

	return NULL;
}

int main(){
	pthread_t tid[THREAD_COUNT];
	ThreadArg args[THREAD_COUNT];

	int ret;
	for(int i = 0;i < THREAD_COUNT;i++){
		args[i].thread_id = i;
		args[i].msg = "Hello from Thread\n";
		ret = pthread_create(&tid[i],NULL,thread_start,&args[i]);
		if(ret != 0){
			fprintf(stderr,"Failed to creat Thread %d!\n",i);
			exit(1);
		}
	}

	sleep(30);

	return 0;
}

