#include <stdio.h>
#include <errno.h>

int main(){
	int a,b;
	scanf("%d%d",&a,&b);
	printf("a+b=%d\n",a+b);
	errno = 13;
	perror("Test: ");
	fprintf(stderr,"This is Error Message!\n");

	return 0;
}
