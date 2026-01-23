#include "../common/head.h"
#define FIFO_PATH "fifo.txt"
#define BUFF_SIZE 256

void write_mode(){
	printf("prepare to open fifo file\n");
	int fd = open(FIFO_PATH,O_WRONLY);
	printf("fifo file open\n");
	if(fd < 0){
		perror("open FIFO_PATH");
		exit(1);
	}
	char buff[BUFF_SIZE+5] = {0};
	printf("please input data, press CRTL+D to exit\n");
	while(fgets(buff,BUFF_SIZE,stdin)){
		write(fd,buff,strlen(buff));
	}
	close(fd);
}

void read_mode(){
	printf("prepare to open fifo file\n");
	int fd = open(FIFO_PATH,O_RDONLY);
	printf("fifo file open\n");
    if(fd < 0){
        perror("open FIFO_PATH");
        exit(1);
    }
    char buff[BUFF_SIZE+5] = {0};
	printf("waiting for data...\n");
	while(1){
		size_t nread = read(fd,buff,BUFF_SIZE);
		if(nread > 0){
			printf("receive: %s",buff);
		}else if(nread == 0){
			printf("The other side has closed!\n");
			break;
		}else{
			fprintf(stderr,"failed to read!\n");
			break;
		}
		memset(buff,0,BUFF_SIZE+5);
	}
	close(fd);
}

int main(int argc,char** argv){
	if(argc  != 2){
		fprintf(stderr,"Usage: %s [read|writ]\n",argv[0]);
		exit(1);
	}
	if(access(FIFO_PATH,F_OK) == -1){
		if(mkfifo(FIFO_PATH,0666) != 0){
			perror("mkfifo");
			exit(1);
		}		
	}

	if(strcmp(argv[1],"write") == 0){
		write_mode();
	}else if(strcmp(argv[1],"read") == 0){
		read_mode();
	}else{
		fprintf(stderr,"Usage: %s [read|writ]\n",argv[0]);
        exit(1);
	}

	return 0;
}

