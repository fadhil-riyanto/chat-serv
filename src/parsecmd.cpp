#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#include <asm-generic/errno.h>
#include <cstddef>
#endif

#include "header/parsecmd.h"
#include "header/errornum.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

parse_cmd::parse_cmd(int argc, char **argv)
{
    this->argc = argc;
    this->argv = argv;
}


int parse_cmd::get(const char *param, char **ret) {
    char *tempval;
    for(int x = 0; x < this->argc; x++)
    {
        if (x % 2 != 0) {
            if ('-' == this->argv[x][0] && '-' == this->argv[x][1])
            {
                tempval = &this->argv[x][2];
            } else if ('-' == this->argv[x][0]) {
                tempval = &this->argv[x][1];
            }
            if (strcmp(tempval, param) == 0) {
                    if ((x + 1) <= (this->argc - 1)) 
                    {
                        *ret = this->argv[x + 1];
                        return 0;
                    } else {
                        
                        *ret = NULL;
                        return -EINCOMPLETEARG;
                    }
                } 
        }
    }
    *ret = NULL;
    return -ENULL;

}


// char *parse_cmd::get(char *params)
// {
//     return this->data[nums];
// }

