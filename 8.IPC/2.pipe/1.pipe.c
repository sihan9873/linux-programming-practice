#include "../common/head.h"


int main(){
	int fd[2];
	pipe(fd);
	pid_t pid = fork();
	if(pid>0){
		//父进程写,关闭读端
		close(fd[0]);
		char msg[] = "Hello World!";
		write(fd[1],msg,strlen(msg));
		close(fd[1]);
	}else if(pid == 0){
		//子进程读
		close(fd[1]);
		char buff[256] = {0};
		int n = read(fd[0],buff,sizeof(buff));
		printf("子进程收到: %s\n",buff);
		close(fd[0]);
	}

	return 0;
}

