#include "./common/head.h"

void cleanup(void* arg){
	printf("Clean up: %s\n",(char*)arg);
}

void* thread_func(void* arg){
	pthread_cleanup_push(cleanup,"Free Resources");

//	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);

	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);	
	
	//模拟线程工作
	while(1){
		printf("Thread is working...\n");
		sleep(1);
	}

	//实际上不会执行,内核自动操作
	pthread_cleanup_pop(1);
	
	return NULL;
}

int main(){
	pthread_t tid;
	pthread_create(&tid,NULL,thread_func,NULL);

	sleep(2);

	printf("Request cancel...\n");
	pthread_cancel(tid);

	void* res;
	pthread_join(tid,&res);
	if(res == PTHREAD_CANCELED){
		printf("Thread was canceled...\n");
	}

	return 0;
}

