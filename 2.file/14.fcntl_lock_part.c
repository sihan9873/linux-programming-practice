#include "./common/head.h"



int main(int argc,char **argv){
	int fd = open("15.txt",O_RDWR);
	if(fd == -1){
		perror("openfile");
		exit(EXIT_FAILURE);
	}

	return 0;
}
