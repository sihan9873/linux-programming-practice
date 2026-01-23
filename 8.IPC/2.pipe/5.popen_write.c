#include "../common/head.h"
#define MAX_LINE 256

//从管道中读入数据,拍在子进程中对数据排序

int main(){
	FILE* fp;
	fp = popen("sort","w");
	if(fp == NULL){
		perror("popen()");
		exit(1);
	}

	printf("请输入单词,使用CRTL+D结束:\n");
	
	char line[MAX_LINE];
	while(fgets(line,sizeof(line),stdin) != NULL){
		fprintf(fp,"%s",line);
	}

	pclose(fp);

	return 0;
}

