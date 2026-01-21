#include "../common/head.h"

int main(){
	pid_t pid;
	for(int i=0;i<10;i++){
		pid = fork();
		if(pid==0){
			// prevent the child to fork
			break;
		}
	}

	if(pid==0){
		printf("I'm the child!\n");
	}

	if(pid>0){
		for(int i=0;i<10;i++){
			wait(NULL);
		}
		printf("I'm the parent!\n");
	}
	
	return 0;
}

