#ifndef _GNU_SOURCE
#define _GNU_SOURCE 
#endif

#include "src/header/parsecmd.h"
#include "src/header/errornum.h"
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>



int _cmd_interface(int argc, char **argv, parse_cmd *parse_cmd, 
                    cmd_data *cmd_data)
{
    
    int ret;
    char *port, *addr;
    
    parse_cmd->get("addr", &addr);
    if (parse_cmd->get("addr", &addr) == EINCOMPLETEARG ||            \
        parse_cmd->get("addr", &addr) == ENULL)
        goto fail;
    cmd_data->addr = addr;

    if (parse_cmd->get("port", &port) == EINCOMPLETEARG ||              \
        parse_cmd->get("port", &port) == ENULL)
        goto fail;
    
    cmd_data->port = atoi(port);

    fprintf(stdout, "listening on %s:%d\n", 
            cmd_data->addr, cmd_data->port);
    return 0;
fail:
    printf("please use ./%s --port portnumber --addr ipv4addr\n", argv[0]);
    return -1;

}

int main(int argc, char **argv)
{
    struct cmd_data cmd_data;
    parse_cmd parse_cmd(argc, argv);
    return _cmd_interface(argc, argv, &parse_cmd, &cmd_data);


    //fprintf(stdout, "%s\n", buf);
    // return 0;
}