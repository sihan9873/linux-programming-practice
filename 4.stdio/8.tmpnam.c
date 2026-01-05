#include <stdio.h>

int main(){
	char filename[L_tmpnam];
	if(tmpnam(filename) != NULL){
		printf("tmp file name is %s.\n",filename);
		FILE *fp = fopen(filename,"w");
		if(fp == NULL){
			return 1;
		}
		fprintf(fp,"这是临时数据.\n");
		fclose(fp);
		remove(filename);
	}	

	return 0;
}

