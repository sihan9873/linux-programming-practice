#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//extern char *optarg;
//getopt 提供的全局变量,指向当前选项的参数
//getopt 会整理选项和参数 选项在前,参数在后
//
//extern int optind;
//维护一个全局游标,从 argv[1] 开始扫,遇到 - 开头的，就当作选项
//遍历后指向第一个“非选项参数”
//
//optstring选项字符串,表示提供的选项及其参数
// a:选项参数 b::optional选项参数 c ...

char *name = NULL;
int age = 18;
char *gender = "female";

int main(int argc,char **argv){
	int opt;//option character
	while((opt = getopt(argc,argv,"n:a:g:")) != -1){
		switch(opt){
			case 'n':
				name = optarg;	
				break;
			case 'a':
				age = atoi(optarg);
				break;
			case 'g':
				gender = optarg;
				break;
			default:
				fprintf(stderr,"Usage : %s -n name -a age -g gender!\n",argv[0]);
				return 1;
		}
	}
	printf("optind : %d, argv[%d] = %s\n",optind,optind,argv[optind]);
	printf("optarg : %s\n",optarg);
	printf("Name : %s\n",name);
	printf("Age : %d\n",age);
	printf("Gender : %s\n",gender);

	return 0;
}


