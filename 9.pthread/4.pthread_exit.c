#include "./common/head.h"

pthread_key_t key;

void goodbye(void){
	printf("atexit() func called\n");
}

void cleaup_handler(void *arg){
	printf("Clean up: %s\n",(char*)arg);
	
}

void destructor(void *value){
	printf("Destructor called for TSD: %s\n",(char*)value);
	free(value);
}

void* thread_start(void* arg){
	pthread_detach(pthread_self());

	pthread_cleanup_push(cleaup_handler,"Freeing resources");

//	pthread_key_create(&key,destructor);

	char* data = malloc(20);
	sprintf(data,"ThreadData");
	pthread_setspecific(key,data);

	printf("thread is running...\n");
	pthread_exit(NULL);

	pthread_cleanup_pop(1);	
}

int main(){
	pthread_t tid;

	//希望在线程结束的时候做些事情,就在主线程调用此函数
	atexit(goodbye);

	pthread_key_create(&key,destructor);

	pthread_create(&tid,NULL,thread_start,(void*)&tid);
	pthread_join(tid,NULL);
	
	return 0;
}

