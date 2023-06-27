#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#include <cstdio>
#include <cstring>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void show_error_code(int errnum, char *perror_str)
{
    char *buf;
    fprintf(stderr, "(%d) %s: %s\n", 
            errnum, strerrorname_np(errnum), perror_str);
}