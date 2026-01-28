#include "./common/head.h"


int main(){
	//pisix需要先在进程中共享

	int shmid = shmget(0x1234,sizeof(sem_t),IPC_CREAT | 0666);
	if(shmid == -1){
		perror("shmget");
		exit(1);
	}

	sem_t *sem = (sem_t*)shmat(shmid,NULL,0);
	if(sem == (void*)-1){
		perror("shmat");
        exit(1);
	}

	if(sem_init(sem,1,1) == -1){
		perror("sem_init");
		exit(1);
	}

	pid_t pid = fork();
	if(pid < 0){
		perror("fork()");
		sem_destroy(sem);
		exit(1);
	}else if(pid == 0){
		for(int i = 0;i < 10;i++){
			sem_wait(sem);
            printf("Child Start! <%d>\n",i);
            sleep(2);
            printf("Child End! <%d>\n",i);
            sem_post(sem);
            sleep(1);
		}
	}else{
		for(int i = 0;i < 10;i++){
			sleep(1);
			sem_wait(sem);
			printf("I'm Parent! <%d>\n",i);
			sleep(1);
			sem_post(sem);
        }
		wait(NULL);
		sem_destroy(sem);
		shmdt(sem);
		shmctl(shmid,IPC_RMID,NULL);
	}
	return 0;
}

