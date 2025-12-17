#include "../common/head.h"

int make_nonblock(int fd){
	int flag;
 	if((flag = fcntl(fd,F_GETFL)) < 0){
		// 自定义的接口不需要perror,由上层调用函数报错即可
		return -1;
	}

	// 反例: 直接修改位图
	//flag = O_NONBLOCK;
	flag |= O_NONBLOCK;
	return fcntl(fd,F_SETFL,flag);
}

int make_block(int fd){
    int flag;
    if((flag = fcntl(fd,F_GETFL)) < 0){
        return -1;
    }

    // 清除非阻塞
    flag &= ~O_NONBLOCK;
    return fcntl(fd,F_SETFL,flag);
}


