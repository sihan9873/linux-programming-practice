#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int fd;
	close(0);
	fd = open("./1.list_file.c",O_RDONLY);
	if(fd < 0){
		perror("open");
		exit(1);
	}
	printf("fd = %d\n",fd);
	//sleep(600);
	close(fd);
	close(fd);
	perror("close");
	return 0;
}
