#ifndef _COMMON_H
#define _COMMON_H

int make_block(int fd);
int make_nonblock(int fd);

static int max_fd = 0;
static pid_t *child_pid = NULL;
void init_child_pid();
FILE* mypopen(const char* cmd,const char* type);
int mypclose(FILE *fp);

#endif
