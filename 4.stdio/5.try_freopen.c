#include "../common/head.h"

int main(){
	FILE* fip;
	fip = fopen("./.grades.txt","r");
	if(fip == NULL){
		perror("fopen ./.grades.txt: ");
		exit(1);
	}

	FILE* fop;
	fop = fopen("./results.txt","w");
    if(fop == NULL){
        perror("fopen ./results.txt: ");
        exit(1);
    }

	int avg,cnt=0,sum=0,t;
	while(fscanf(fip,"%d",&t) != EOF){
		sum += t;
		cnt++;
	}
	avg = sum/cnt;

	freopen("./results.txt","w",stdout);
	printf("sum = %d,cnt = %d,sum/cnt = %d,avg = %d\n",sum,cnt,sum/cnt,avg);
//	fprintf(fop,"%d",avg);
	

	fclose(fip);
	fclose(fop);

	return 0;
}
