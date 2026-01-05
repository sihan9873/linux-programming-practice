#include <stdio.h>

int main(){
	FILE *temp = tmpfile();
	if(temp == NULL){
		perror("tmpfile");
		return 1;
	}

	fprintf(temp,"临时文件数据.\n");
	rewind(temp);
	char buffer[512] = {0};
	fgets(buffer,sizeof(buffer)-1,temp);
	printf("<Read> = %s",buffer);

	return 0;
}

