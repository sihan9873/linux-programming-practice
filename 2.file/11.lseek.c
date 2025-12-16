#include "./common/head.h"

int main(){
	int fd = open("./test.txt",O_RDONLY);
	// if(fd == -1)
	if(fd < 0){
		perror("Failed to open the file");
		exit(EXIT_FAILURE);
	}

	off_t len = lseek(fd,0,SEEK_END);
	// offset = 0,SEEK_END,指向文件末尾
	// lseek返回文件从文件开始到指针位置的字节大小,即文件大小									
	if(len == -1){
		perror("Failed to get the length of the file");
		exit(EXIT_FAILURE);
    }

	printf("The length of the file is %ld\n",len);

	off_t mid_pos = len/2;
	
	// 找到文件的中间位置
	if(lseek(fd, mid_pos,SEEK_SET) == -1){
		perror("Failed to move the cursor");
		exit(EXIT_FAILURE);
	}

	// 系统编程要点:
	// 1.检查每个系统调用的返回值
	// 2.注意缓存器大小,注意读写的不同
	// 读多少写多少
	// 读文件小诀窍
	// 1.
	// char buff[512 + 1] = {0};
	// size_t buff_size = 512;;
	char buff[512] = {0};
	// ssize_t nread = read(fd,buff,buff_size);
	// 2.
	ssize_t nread = read(fd,buff,sizeof(buff)-1);
	// 3.
	// ssize_t nread = read(fd,buff,sizeof(buff));
	// buff[nread] = '\0';
	// 这个操作仍有风险,因此我们常常在定义长度时+5
	// #define MAX_SIZE 512
	// char buff[MAX_SIZE + 5] = {0};
	if(nread < 0){
        perror("Failed to read the file");
        exit(EXIT_FAILURE);
    }
		
	printf("The content of the file is:\n%s\n",buff);

	close(fd);	

	return 0;
}
