#include "./common/head.h"


int main(){
	FILE *fp = mypopen("ls -1","r");
	char buff[256] = {0};
	while(fgets(buff,256,fp) != NULL){
		printf("%s",buff);
		memset(buff,0,256);
	}

	mypclose(fp);
		
	return 0;
}

