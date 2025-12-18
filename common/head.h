#ifndef _HEAD_H
#define _HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <utime.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <math.h>

#include "common.h"
#include "color.h"

#ifdef _D
#define DBG(fmt,args...) printf(fmt,##args)
#else
#define DBG(fmt,args...)
#endif

#endif
