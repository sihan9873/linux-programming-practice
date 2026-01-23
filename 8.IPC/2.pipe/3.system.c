#include "../common/head.h"

/*
运行这个程序,在命令行输入ps -ef,可以看到类似结果
sihan       5577     293  0 13:55 pts/0    00:00:00 ./a.out
sihan       5581    5577  0 13:55 pts/0    00:00:00 sh -c -- sleep 20
sihan       5582    5581  0 13:55 pts/0    00:00:00 sleep 20

system()是c语言与系统之间最简单的接口,
但有很多缺点,返回值简单,没办法获取命令行的输出,
没有输入流控制,
有安全风险
更推荐popen()
*/

int main(){
	int ret = system(NULL);
	printf("ret = %d\n",ret);

	system("ls -a");

	system("sleep 20");

	system("echo Done");

	return 0;
}

