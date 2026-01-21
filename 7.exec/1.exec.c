#define _GNU_SOURCE
#include "./common/head.h"

int main(){

//	execl("/usr/bin/ls","ls",".","/",(char*)NULL);

//	execlp("ls","ls",".","/",(char*)NULL);

	char *args[]={
		"ls111",
		".",
		"/",
		NULL
	};

//	execvp("ls",args);

	extern char **environ;
	for(int i=0;environ[i]!=NULL;i++){
		printf("%s\n",environ[i]);
	}

	char* env[] = {
		"PATH=.",
		NULL
	};

	printf("pid is %d\n",getpid());

	execvpe("./testexec",args,env);
	perror("execvpe failed");

	printf("Program is Over\n");
	return 0;
}

