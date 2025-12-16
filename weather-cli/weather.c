#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* city=NULL;
int all=0;
int temp=0;
int st=0;
int help=0;
int vers=0;

typedef struct {
	char *city;
	int temp;
	char *status;
	char *emoji;
} weather;

weather data[]={
	{"Beijing",25,"晴天","☀️"},
	{"Shanghai", 20, "多云", "☁️"},
    	{"Guangzhou", 28, "下雨", "🌧️"},
    	{"Harbin", -5, "下雪", "❄️"}
};

int data_size = sizeof(data)/sizeof(data[0]);

void print_weather(weather w,int show_temp,int show_status){
	if(show_temp && show_status){
		printf("%s: %d°C %s\n",w.city,w.temp,w.emoji);
    	}else if(show_temp){
        	printf("%s: %d°C\n",w.city,w.temp);
    	}else if(show_status){
        	printf("%s: %s\n", w.city, w.emoji);
    	}else{
        	// 默认显示完整信息
        	printf("%s: %d°C %s\n",w.city,w.temp,w.emoji);
    	}
	return;
}

int main(int argc,char **argv){
	int opt;
	while((opt = getopt(argc,argv,"c:tsahv")) != -1){
		switch(opt){
			case 'c':
				city = optarg;
				break;
			case 't':
				temp=1;
				break;

			case 's':
				st=1;
				break;
			case 'a':
				all=1;
				break;
			case 'h':
				help=1;
				break;
			case 'v':
				vers=1;
				break;
			default:
				fprintf(stderr,"%s",
		"Usage: weather -c city -a (show all) -t (show temperature) -h (show help) -v(show version)");
		}
	}

	if(help){
		printf(
		"Usage: weather -c city -a (show all) -t (show temperature) -h (show help) -v(show version)");
	}
	if(vers){
		printf("weather_cli version 1.0\n");
	}
	if(all){
		for(int i=0;i<data_size;i++){
                	print_weather(data[i],temp,st);
                }
	}else if(city){
		int found=0;
		for(int i=0;i<data_size;i++){
			if(strcmp(data[i].city,city)==0){
				print_weather(data[i],temp,st);
				found=1;
				break;
			}
		}	
		if(!found){
			fprintf(stderr, "Unknown city: %s\n", city);
		}
	}else {
		fprintf(stderr, "Please specify -c <city> or -a\n");
	}

	return 0;
}
