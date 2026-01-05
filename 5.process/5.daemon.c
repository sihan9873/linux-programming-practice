#include "../common/head.h"

void init_daemon(){
	pid_t pid;
	pid = fork();
	if(pid < 0){
		perror("fork error");
		exit(EXIT_FAILURE);
	}else if(pid > 0){
		//母进程
		//1.守护进程不需要母进程,直接退出
		exit(EXIT_SUCCESS);		
	}
	//子进程需要做的事
	//setsid - creates a session and sets the process group ID	
	//见man 2 setsid

	//2.创建会话
	// 让这个守护进程彻底不再属于任何终端
	if(setsid()<0){
		perror("setsid error");
		exit(EXIT_FAILURE);
	}
	
	//3.切换工作目录(必须存在)
	//每个进程都有一个属性：current working directory（cwd,当前工作目录）
	//如果不更改工作目录,那么当前目录所在文件系统会被内核认为被占用
	//这违背了守护进程的原则:不应该占用任何用户目录或可卸载资源
	if(chdir("/")<0){
		perror("chdir error");
		exit(EXIT_FAILURE);
	}

	//4.关闭文件,比如每个进程原有的012
	//此前的perror还是可以输出的,因为程序是线性执行的
	freopen("/dev/null","r",stdin);
	freopen("/dev/null","w",stdout);
	freopen("/dev/null","w",stderr);
}

void broadcast_time(){
	///"dev/pts/*" 是每一个登录用户的终端窗口，对应的设备文件

	// 整点报时广播
	// 遍历目录下的pts虚拟终端设备
	// 目录流指针
	DIR *dir;
	//目录项结构体
	struct dirent *entry;
	char *dev_path = "/dev/pts";
	char full_path[512];
	int fd;
	char msg[512] = {0};

	time_t now;
    struct tm *timeinfo;
    time(&now);
    timeinfo = localtime(&now);
	
	snprintf(msg,sizeof(msg)-1,"\n您好,当前时间是: %02d:%02d:%02d\n",
		timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec
	);	

	//打开目录流
	dir = opendir(dev_path);
	if(dir == NULL){
		perror("Failed to open dev_path");
		exit(EXIT_FAILURE);
	}

	while((entry = readdir(dir)) != NULL){
		if(entry->d_name[0] < '0' || entry->d_name[0] > '9'){
			continue;
		}
		//计算当前文件路径
		//初始化
		memset(full_path,0,sizeof(full_path));
		snprintf(full_path,sizeof(full_path),"%s/%s",dev_path,entry->d_name);
		fd = open(full_path,O_WRONLY | O_NONBLOCK);
		if(fd < 0){
			perror("fopen");
			exit(EXIT_FAILURE);
		}	
		write(fd,msg,strlen(msg));
		close(fd);
	}
	closedir(dir);
	return;
}

int main(){
	// A.实现一个守护进程
	init_daemon();

	//守护者进程在死循环中工作
	while(1){
		//B.实现整点报时功能
		time_t now;
		//vim -t tm: 查看时间信息结构体定义
		struct tm *timeinfo;
		time(&now);
		timeinfo = localtime(&now);	
		
		//测试时间
//		if(timeinfo->tm_min == 21 && timeinfo->tm_sec == 0){
		if(timeinfo->tm_min == 0 && timeinfo->tm_sec == 0){
			// C.实现广播功能
			//printf("整点报时广播!\n");
			broadcast_time();
		}

		//希望此功能1秒执行一次
		sleep(1);
	}		

	return 0;
}

