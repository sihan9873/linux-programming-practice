#include "../common/head.h"


int main(){
	pid_t pid;
	pid = fork();
	if(pid>0){
		//母进程先死
		sleep(20);
	}
	//子进程sleep
	sleep(1000);

	return 0;
}

