#include "./common/head.h"

void write_to_log(const char* log_message){
	int fd = open("./13.log",O_WRONLY | O_CREAT,0644);;
	if(fd == -1){
		perror("Failed to open log file");
		exit(EXIT_FAILURE);
	}

	struct flock lock;
	memset(&lock,0,sizeof(lock));
	// 申请lock结构体,加写锁
	lock.l_type = F_WRLCK;
	
	// 加建议锁
	// 若锁被持有,等待信号量
	if(fcntl(fd,F_SETLKW,&lock) == -1){
		perror("Failed to lock the file");
		close(fd);
		exit(EXIT_FAILURE);
	}

	// 移动读写位置
	if(lseek(fd,0,SEEK_END) == -1){
		perror("Failed to seek to eof");
		close(fd);
        exit(EXIT_FAILURE);
	}
	//此处不能使用sizeof!
	//1.因为数据大小不一定用完剩下的空间
	//2.sizeof不一定得到内容大小,而是内容指针的大小
	size_t wnum = write(fd,log_message,strlen(log_message));
	if(wnum == -1){
		perror("Failed to write the log");
		close(fd);
        exit(EXIT_FAILURE);
    }

	write(fd,"\n",1);
	// 模拟写文件
	sleep(5);
	printf("Write to log file success!\n");
	
	lock.l_type = F_UNLCK;
	if(fcntl(fd,F_SETLK,&lock) == -1){
		perror("Failed to unlock the file");
        close(fd);
        exit(EXIT_FAILURE);
	}

	close(fd);
	return;
}

int main(int argc,char **argv){
	if(argc != 2){
		fprintf(stderr,"Usage : %s log message\n",argv[0]);
		exit(1);
	}
	write_to_log(argv[1]);

	return 0;
}
