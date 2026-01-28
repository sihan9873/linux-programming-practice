#include "./common/head.h"

void sem_p(int semid){
	struct sembuf p ={0,-1,0};
	if(semop(semid,&p,1) == -1){
		perror("semop");
		exit(1);
	}
}

void sem_v(int semid){
    struct sembuf v ={0,1,0};
    if(semop(semid,&v,1) == -1){
        perror("semop");
        exit(1);
    }
}

int main(){
	key_t key = ftok(".",2025);
	if(key == -1){
		perror("ftok()");
		exit(1);
	}

	int semid = semget(key,1,IPC_CREAT | 0666);
	if(semid < 0){
		perror("semget()");
        exit(1);
	}

	if(semctl(semid,0,SETVAL,1) == -1){
		perror("se,ctl()");
		exit(1);
	}

/*
	模拟:
		子进程运行时,父进程需要等待
		也就是,子进程打印的字符串之间,不能有父进程打印的字符串
*/

	pid_t pid = fork();
	if(pid < 0){
		perror("fork()");
        exit(1);
	}else if(pid == 0){
		for(int i = 0;i < 10;i++){
			sem_p(semid);
			printf("Child Start! <%d>\n",i);
			sleep(2);
			printf("Child End! <%d>\n",i);
			sem_v(semid);
			sleep(1);
		}
	}else{
		for(int i = 0;i < 10;i++){
			sem_p(semid);
            printf("I'm Parent! <%d>\n",i);
			sleep(1);
			sem_v(semid);
        }
	}


		
	return 0;
}

