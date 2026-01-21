#include "./common/head.h"

int i=0;

void restart(int signum){
	i=0;
}

int main(){
	//初始化结构体
	struct sigaction sa;
	sa.sa_handler = restart;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	
	//安装信号处理规则
	if(sigaction(SIGINT,&sa,NULL) == -1){
		perror("sigation");
		exit(1);
	}

	for(;i<100000;i++){
		printf("%d\n",i);
		sleep(1);
	}

	return 0;
}

