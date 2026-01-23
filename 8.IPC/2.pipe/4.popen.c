#include "../common/head.h"

int main(){
	FILE *fp;
	char buff[512] = {0};

	fp = popen("ls -l","r");
	if(fp == NULL){
		perror("popen()");
		exit(1);
	}
	//popen实际上做的事:创建pipe,fork子进程,exec...
	
	printf("命令正在执行中,输出如下:\n");
	while(fgets(buff,sizeof(buff),fp) != NULL){
		printf("%s",buff);
		memset(buff,0,sizeof(buff));
	}
	
	return 0;
}

