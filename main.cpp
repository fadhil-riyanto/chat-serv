#ifndef _GNU_SOURCE
#define _GNU_SOURCE 
#endif

#include "src/header/parsecmd.h"
#include "src/header/errornum.h"
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>

struct cmd_data {
    int         port;
    char        *addr;
};

int _cmd_interface(int argc, char **argv, parse_cmd *parse_cmd) {
    
    int ret;
    char *buf;

    if (parse_cmd->get("port", &buf) == EINCOMPLETEARG)
    {
        printf("please use ./%s --port portnumber --addr ipv4addr\n", )
    }

    fprintf(stdout, "%s\n", buf);

    return 0;

}

int main(int argc, char **argv)
{
    parse_cmd parse_cmd(argc, argv);
    return _main(&parse_cmd);


    //fprintf(stdout, "%s\n", buf);
    return 0;
}