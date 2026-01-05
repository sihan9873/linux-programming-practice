#include "../common/head.h"

/*
bash -> 母进程(运行结束) -> bash -> 子进程
实际运行情况:
sihan@LAPTOP-644PDUBQ:~/anji/sys/5.process$ ./a.out
this is before fork()
this is the parent process! <pid = 1897>
sihan@LAPTOP-644PDUBQ:~/anji/sys/5.process$ this is the child process! <pid = 1898>
*/

int main(){
	printf("this is before fork()\n");

	pid_t pid;
	if((pid=fork()) < 0){
		perror("fork()");
		exit(1);
	}
	if(pid>0){
		printf("this is the parent process! <pid = %d>\n",getpid());
	}else{
        printf("this is the child process! <pid = %d>\n",getpid());
		exit(1);
	}

	

	return 0;
}

