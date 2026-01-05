#include "../common/head.h"

int main(){
	pid_t pid;
	
	for(int i=0;i<100;i++){
		pid = fork();
		if(pid < 0){
			perror("fork()");
			exit(1);
		}else if(pid == 0){
			printf("<%d>th child process,pid = %d.\n",i,getpid());
			break;
		}
	}
	
	if(pid!=0){
		printf("this is parent process!\n");
	}
	
	return 0;
}

