#include "../common/head.h"

int main(){
	FILE *fp;
	fp = fopen("./.input.txt","r");
	if(fp == NULL){
		perror("fopen");
		exit(1);
	}

//	char buffer[1024] = {0};
//	printf("buffer = %s\n",buffer);	
//	fread(buffer,1,1024,fp);

	// 此时.input.txt中有两个整型	
	int a,b;
	fscanf(fp,"%d%d",&a,&b);
	printf("a+b = %d\n",a+b);


	fclose(fp);
	

	return 0;
}



