#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "header/server.h"
#include "error.cpp"
#include <asm-generic/errno.h>
#include "netinet/in.h"
#include "sys/socket.h"
#include <arpa/inet.h>
#include <cerrno>
#include <stdio.h>
#include <unistd.h>
#include "header/data.h"
#include <sys/socket.h>

#define LISTEN_BACKLOG 50

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
    return ret;

}

int sock::sock_listen()
{
    int ret;
    ret = listen(this->server_state->fd, LISTEN_BACKLOG);
    if (ret < 0) {
        return -errno;
        goto onerr;
    }
    return ret;
onerr:
    close(this->server_state->fd);
    return ret;
}

void sock::on_accept(void (*f) (struct mainthread_data *mainthread_data) )
{
    int client = -1;
    struct sockaddr_in client_name;
    socklen_t client_name_len = sizeof(client_name);

    while(1)
    {
        client = accept(this->server_state->fd, (struct sockaddr*)&client_name, 
            &client_name_len);

    }
}

int sock::start()
{
    int ret;
    if ((ret = this->sock_create_fd()) < 0)
    {
        perror("sock::sock_create_fd() on socket()");
        return errno;
    }

    if ((ret = this->sock_bind()) < 0)
    {
        perror("sock::sock_bind() on bind()");
        return errno;
    }
    //this->sock_bind();
    //show_error_code(errno, "bind");

    // if ((ret = this->sock_listen()) <= 0)
    // {
    //     perror("sock::sock_listen() on listen()");
    //     return errno;
    // }
    

    printf("data %d\n", this->sock_listen());
    while(1)
    {
        
    }
    return 0;
}