#include "./common/head.h"

void copy_file(const char *src,const char *dest,int copy_flag){
    int src_fd,dest_fd;
    if((src_fd = open(src,O_RDONLY)) < 0){
        perror("open src");
        exit(1);
    }
    if((dest_fd = open(dest,O_RDWR | O_CREAT, 0600)) < 0){
                perror("open dest");
                exit(1);
    }
    const size_t BUFFSIZE = 5;
    char buff[BUFFSIZE+1];
    size_t rsize = 0;
    memset(buff,0,BUFFSIZE+1);

    while((rsize = read(src_fd,buff,BUFFSIZE)) > 0){
        write(dest_fd,buff,rsize);
    }
	
	if(copy_flag){
		// 定义stat结构体，用于存储源文件的元数据
		struct stat src_stat;
		// 读取已打开的源文件的元数据
		if(fstat(src_fd,&src_stat) < 0){
			perror("fstat");
		}else{
			// 将源文件的权限（st_mode中的权限位）复制到目标文件
			if(fchmod(dest_fd,src_stat.st_mode) < 0){
				perror("fchmod");
			}
			// 复制文件访问(access)时间和编辑(modify)时间,另外修改权限叫做change
			// 定义接收数据结构,见man utime
			struct utimbuf new_time;
			new_time.actime = src_stat.st_atime; 			
			new_time.modtime = src_stat.st_mtime;
			if(utime(dest,&new_time) < 0){
				perror("utime");
			}
		}	
	}

    close(src_fd);
    close(dest_fd);

    return;
}

int main(int argc,char **argv){
	int opt,copy_flag=0;

	while((opt = getopt(argc,argv,"a")) != -1){
		switch (opt){
			case 'a':
				copy_flag=1;
				break;
			default:
				fprintf(stderr,"Usage : %s [-a] <src_file> <dest_file>\n",argv[0]);
				exit(1);
		}
	}

	// 参数数量应该等于2
	if(argc - optind != 2){
		fprintf(stderr,"Usage : %s [-a] <src_file> <dest_file>\n",argv[0]);
        exit(1);
	}

	const char *src = argv[optind];
	const char *dest = argv[optind+1];

	copy_file(src,dest,copy_flag);	
	
	return 0;
}
