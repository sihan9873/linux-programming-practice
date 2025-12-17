#include "./common/head.h"

int main(){
	int age;
	make_nonblock(0);
	int ret = scanf("%d", &age);
	if(ret < 0){
		perror("scanf");
		exit(1);
	}
	printf("I am %d years old.\n",age);

	return 0;
}
