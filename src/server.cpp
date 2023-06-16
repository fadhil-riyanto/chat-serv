#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#include <sys/socket.h>
#include <unistd.h>
#endif

#include "header/server.h"
#include <asm-generic/errno.h>
#include "netinet/in.h"
#include "sys/socket.h"
#include <arpa/inet.h>
#include <cerrno>
#include <stdio.h>

sock::sock(struct cmd_data *cmd_data)
{
    struct server_state server_state;

    this->cmd_data = cmd_data;
    this->server_state = &server_state;
    
}

int sock::sock_create_fd()
{
    int ret;
    ret = socket(AF_INET, SOCK_STREAM, 0);
    if (ret < 1)
        return errno;
    this->server_state->fd = ret;
    return ret;
}

int sock::sock_bind()
{
    int ret; 
    struct sockaddr_in sockaddr;

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(this->cmd_data->port);
    sockaddr.sin_addr.s_addr = inet_addr(this->cmd_data->addr);

    ret = bind(this->server_state->fd, (struct sockaddr*)&sockaddr, (socklen_t)sizeof(sockaddr));
    printf("%d\n", errno);
    return ret;

}

int sock::start()
{
    int ret;
    if ((ret = this->sock_create_fd()) < 1)
    {
        perror("sock::sock_create_fd() on socket()");
        return EBADFD;
    }

    printf("data %d\n", this->sock_bind());
    return 0;
}