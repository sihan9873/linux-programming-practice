#include "./common/head.h"

//创建多个参数的单线程`

typedef struct {
	char name[20];
	int age;
} ThreadArg;

void *thread_start(void* arg){
	ThreadArg *info = (ThreadArg*)arg;
	printf("In the thread,I am %s, and I'm %d years old!\n",info->name,info->age);
	return(NULL);
}

int main(){
	pthread_t tid;
	ThreadArg info;
	strcat(info.name,"sihan");
	info.age = 18;
	pthread_create(&tid,NULL,thread_start,(void*)&info);

	//主线程结束,所有子线程也会随之结束,需要阻塞等待
	sleep(2);

	return 0;
}

