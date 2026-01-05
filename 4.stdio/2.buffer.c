#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 一个演示程序: 
// 在没有换行符的情况下,
// 会在缓冲区满,或者程序运行结束输出

int main(){
	printf("Hello World!");
	// 子进程是从当前程序的当前行运行
	// 但由于复制了当前的缓冲区,所以在子程序结束时也会有输出
	fork();


//	printf("\n");
//	fflush(stdout);

	sleep(60);

	return 0;
}
