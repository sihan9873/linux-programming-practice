#include "../common/head.h"

int main(){
	pid_t pid;
	pid = fork();
	if(pid==0){
		//子进程
		exit(1);
	}
	//让母进程休眠,不回收子进程
	sleep(1000);
	
	return 0;
}

