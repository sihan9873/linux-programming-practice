#include "./common/head.h"

int i=0;

void restart(int signum){
	i=0;
}

int main(){
	//信号处理
	signal(SIGINT, restart);	

	for(;i<1000000;i++){
		printf("%d\n",i);
		sleep(1);
	}

	return 0;
}

