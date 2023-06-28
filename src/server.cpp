#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#include <cstddef>
#include <cstdlib>
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
#include <pthread.h>

#define LISTEN_BACKLOG 50

typedef struct pthread_arg_t
{
    int                 sockfd;
    struct sockaddr_in  clientaddr;
} pthread_arg_t;

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

void* sock::goto_backend(void *arg)
{
    pthread_arg_t *pthread_arg = (pthread_arg_t*)arg;
    
    const char *buf = (char*)"oke\n";
    size_t buflen = sizeof(buf); 
    //send(pthread_arg->sockfd, buf, buflen, MSG_DONTWAIT);
    write(pthread_arg->sockfd, buf, strlen(buf));
    close(pthread_arg->sockfd);

    // printf("%s", "wokr");
    return 0;
}

void sock::on_accept()
{
    int client = -1;
    int thread_return;
    struct sockaddr_in client_name;
    socklen_t client_name_len = sizeof(client_name);

    pthread_attr_t pthread_attr;
    pthread_arg_t *pthread_arg;
    pthread_t new_thread;

    pthread_arg = (pthread_arg_t*)malloc(sizeof(*pthread_arg));
    
    if(pthread_attr_init(&pthread_attr) != 0)
    {
        show_error_code(errno,  (char*)"pthread attr init");
        free(pthread_arg);
        close(this->server_state->fd);
        exit(-errno);
    }

    if(pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_DETACHED) != 0)
    {
        show_error_code(errno,  (char*)"pthread attr set detachstate");
        free(pthread_arg);
        close(this->server_state->fd);
        exit(-errno);
    }

    while(1)
    {
        client = accept(this->server_state->fd, (struct sockaddr*)&client_name, 
            &client_name_len);
        if (client == -1)
        {
            show_error_code(errno, (char*)"accept");
            goto accept_err;
        }

        pthread_arg->sockfd = client;
        pthread_arg->clientaddr = client_name;




        thread_return = pthread_create(&new_thread, &pthread_attr, sock::goto_backend, (void*)pthread_arg);

        if thread_return == 
    }

accept_err:
    close(this->server_state->fd);
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
    if ((ret = this->sock_listen()) < 0)
    {
        perror("sock::sock_listen() ons listen()");
     
    }
    
    
    this->on_accept();
    
    return 0;
}