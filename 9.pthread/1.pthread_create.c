#include "./common/head.h"

//基础单线程

typedef struct {
	char name[20];
	int age;
} ThreadArg;

void *thread_start(void* arg){
	int *age = (int*)arg;
	printf("In the thread,I am %d years old!\n",*age);

	(*age)++;

	

	fflush(stdout);
	return(NULL);
}

int main(){
	pthread_t tid;
	int age = 18;
	pthread_create(&tid,NULL,thread_start,(void*)&age);
	
	

	printf("tid = <%ld>\n",tid);

	//主线程结束,所有子线程也会随之结束,需要阻塞等待
	sleep(2);

	printf("age = %d\n\n",age);

	return 0;
}

