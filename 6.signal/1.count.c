#include "./common/head.h"

int main(){
	int i=0;
	for(;i<1000000;i++){
		printf("%d\n",i);
		sleep(1);
	}

	return 0;
}

