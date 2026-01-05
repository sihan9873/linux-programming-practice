#include "../common/head.h"

#define MAX_WORD_LEN 50
#define MAX_LINE_LEN 1024
#define MAX_WORDS 1000

//索引项结构
typedef struct{
	char word[MAX_WORD_LEN];
	int line_numbers[MAX_LINE_LEN];
	int count;
} IndexItem;

typedef struct{
	IndexItem items[MAX_WORDS];
	int size;
} IndexDB;

void init_index(IndexDB *db);
void add_to_index(IndexDB *db,const char* word,int line_num);
void build_index(IndexDB *db,const char *word);
void search_word(const IndexDB *db,const char *word);

int main(int argc,char **argv){
	IndexDB db;
	init_index(&db);
	build_index(&db,"sample.txt");
//	search_word(&db,"hello");
//	search_word(&db,"world");
	for(int i=0;i<argc-1;i++){
		search_word(&db,argv[i+1]);
	}

	return 0;
}

void init_index(IndexDB *db){
	db->size = 0;
}

void add_to_index(IndexDB *db,const char* word,int line_num){
	//单词是否在索引中?
	//遍历索引节点
	for(int i=0;i<db->size;i++){
		if(strcmp(word,db->items[i].word)==0){
			//上一个行号不等于当前行号
			if(db->items[i].line_numbers[db->items[i].count-1] != line_num){
				db->items[i].line_numbers[db->items[i].count]=line_num;
    			db->items[i].count++;
			}
			return;
		}
	}

	//索引库大小足够,添加新的索引项
	if(db->size < MAX_WORDS){
		strcpy(db->items[db->size].word,word);
		db->items[db->size].line_numbers[0] = line_num;
		db->items[db->size].count = 1;
		db->size++;
	}

	return;
}

void build_index(IndexDB *db,const char *filename){
	//打开文件
	FILE *fp = fopen(filename,"r");
	if(!fp){
		perror("Failed to open file");
		return;
	}

	//遍历文件
	char line[MAX_LINE_LEN];
	char word[MAX_WORD_LEN];
	int line_num = 0;
	//在文件中按行读取
	while(fgets(line,sizeof(line),fp)){
		//记录行号
		line_num++;
		char *ptr = line;
		//单词长度
		int word_len = 0;
		//在行中拆分单词
		while(*ptr){
			if(isalnum(*ptr)){
				word[word_len++] = tolower(*ptr);
			}else{
				//遇到非字母或数字,说明需要把前面的单词加入索引库
				if(word_len>0){
					word[word_len] = '\0';
					add_to_index(db,word,line_num);
					word_len = 0;
				}
			}
			ptr++;
		}
		//在ptr遇到结束符结束循环前,可能仍有单词没有处理
		if(word_len > 0){
			word[word_len] = '\0';
            add_to_index(db,word,line_num);
           	word_len = 0;
		}
	}
	//关闭文件
	fclose(fp);
	return;
}

void search_word(const IndexDB *db,const char *word){
	for(int i=0;i<db->size;i++){
		if(strcmp(word,db->items[i].word)==0){
            printf("%s 已经找到! 存在于一下行: \n",word);
			for(int j=0;j<db->items[i].count;j++){
				printf("%d ",db->items[i].line_numbers[j]);
			}
			printf("\n");
   			return;
        }
    }
	printf("%s 未找到!\n",word);
	return;
}





