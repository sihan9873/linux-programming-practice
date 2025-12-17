#include "./common/head.h"



int main(int argc,char **argv){
	int fd = open("15.txt",O_RDWR);
	if(fd == -1){
		perror("openfile");
		exit(EXIT_FAILURE);
	}
	
	struct flock lock;
	memset(&lock,0,sizeof(lock));
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	//l_len: 锁定的字节数（设为 0 表示锁定到文件末尾）
	lock.l_len = 100;

	// F_SETLKW	阻塞加锁：锁被占用时阻塞等待，直到锁释放或被信号中断	
	if(fcntl(fd,F_SETLKW,&lock) == -1){
		perror("lock");
		close(fd);
        exit(EXIT_FAILURE);
	}
	printf("First 100 bytes of the file are locked. Press Enter to unlock\n");
	getchar();// 阻塞

	char buff[105] = {0};
	lseek(fd,0,SEEK_SET);
	ssize_t rnum = read(fd,buff,100);
	if(rnum == -1){
		perror("read");
        close(fd);
        exit(EXIT_FAILURE);
	}
	buff[rnum] = '\0';
	printf("First 100 bytes is : \n%s\n",buff);

	lock.l_type = F_UNLCK;
	if(fcntl(fd,F_SETLK,&lock) == -1){
		perror("unlock");
        close(fd);
        exit(EXIT_FAILURE);
    }
	printf("File is unlocked!\n");
	
	close(fd);
	
	return 0;
}
