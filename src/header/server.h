#ifndef SERVER_H
#define SERVER_H

#include <cstddef>
#include <sys/socket.h>
#include "parsecmd.h"

struct server_state
{
    int fd;
};

class sock
{
    private:
    struct cmd_data *cmd_data;
    struct server_state *server_state;
    int sock_create_fd();
    int sock_bind();
    int sock_listen();

    public:
    sock(struct cmd_data *cmd_data);
    int start();
};

#endif