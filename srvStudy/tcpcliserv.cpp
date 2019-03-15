//
//  tcpcliserv.cpp
//  serStudy
//
//  Created by John on 2019/3/13.
//  Copyright © 2019 John. All rights reserved.
//

#include "../lib/lib.h"

struct args {
    long arg1;
    long arg2;
};

struct result {
    long sum;
};

#pragma mark -

void
sig_chld(int signo)
{
    pid_t    pid;
    int        stat;
    
    pid = wait(&stat);
    printf("child %d terminated\n", pid);
    return;
}

void
sig_chld_waitpid(int signo)
{
    pid_t    pid;
    int        stat;
    
    while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0) {
        printf("child %d terminated\n", pid);
    }

    return;
}

#pragma mark -

void
str_echo08(int sockfd)
{
    long arg1, arg2;
    ssize_t n;
    char line[MAXLINE];
    
    for (; ; ) {
        if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
            return;
        if (sscanf(line, "%ld%ld", &arg1, &arg2) == 2)
            snprintf(line, sizeof(line), "%ld\n", arg1 + arg2);
        else
            snprintf(line, sizeof(line), "input error\n");
        n = strlen(line);
        Writen(sockfd, line, n);
    }
}

void
str_echo09(int sockfd)
{
    ssize_t n;
    struct args args;
    struct result result;
    
    for (; ; ) {
        if ( (n = Readn(sockfd, &args, sizeof(args))) == 0)
            return;
        result.sum = args.arg1 + args.arg2;
        Writen(sockfd, &result, sizeof(result));
    }
}

#pragma mark -

void
tcpserv01() {
    PRINT_FUNC
    
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);
    
    for (; ; ) {
        clilen = sizeof(cliaddr);
        connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        
        if ( (childpid = Fork()) == 0) { /* child process */
            Close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        
        Close(connfd);
    }
}

void
tcpserv02() {
    PRINT_FUNC
    
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);
    
    Signal(SIGCHLD, sig_chld);
    
    for (; ; ) {
        clilen = sizeof(cliaddr);
        connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        
        if ( (childpid = Fork()) == 0) { /* child process */
            Close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        
        Close(connfd);
    }
}

void
tcpserv03() {
    PRINT_FUNC
    
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);
    
    Signal(SIGCHLD, sig_chld);
    
    for (; ; ) {
        clilen = sizeof(cliaddr);
        if ( (connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) < 0) {
            if (errno == EINTR)
                continue;
            else
                err_sys("accept error");
        }
        
        if ( (childpid = Fork()) == 0) { /* child process */
            Close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        
        Close(connfd);
    }
}

void
tcpserv04() {
    PRINT_FUNC
    
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);
    
    Signal(SIGCHLD, sig_chld_waitpid);
    
    for (; ; ) {
        clilen = sizeof(cliaddr);
        if ( (connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) < 0) {
            if (errno == EINTR)
                continue;
            else
                err_sys("accept error");
        }
        
        if ( (childpid = Fork()) == 0) { /* child process */
            Close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        
        Close(connfd);
    }
}

void
tcpserv08() {
    PRINT_FUNC
    
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);
    
    Signal(SIGCHLD, sig_chld_waitpid);
    
    for (; ; ) {
        clilen = sizeof(cliaddr);
        if ( (connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) < 0) {
            if (errno == EINTR)
                continue;
            else
                err_sys("accept error");
        }
        
        if ( (childpid = Fork()) == 0) { /* child process */
            Close(listenfd);
            str_echo08(connfd);
            exit(0);
        }
        
        Close(connfd);
    }
}

void
tcpserv09() {
    PRINT_FUNC
    
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);
    
    Signal(SIGCHLD, sig_chld_waitpid);
    
    for (; ; ) {
        clilen = sizeof(cliaddr);
        if ( (connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) < 0) {
            if (errno == EINTR)
                continue;
            else
                err_sys("accept error");
        }
        
        if ( (childpid = Fork()) == 0) { /* child process */
            Close(listenfd);
            str_echo09(connfd);
            exit(0);
        }
        
        Close(connfd);
    }
}

void
tcpservselect01() {
    PRINT_FUNC
  
    int     i, maxi, maxfd, listenfd, connfd, sockfd;
    int     nready, client[FD_SETSIZE];
    ssize_t n;
    fd_set  rset, allset;
    char    buf[MAXLINE];
    socklen_t clilen;
    struct  sockaddr_in cliaddr, servaddr;
    
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    Listen(listenfd, LISTENQ);
    
    maxfd = listenfd;
    maxi = -1;
    for (i = 0; i < FD_SETSIZE; ++i) {
        client[i] = -1;
    }
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);
    
    for (; ; ) {
        rset = allset;
        nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);
        
        if (FD_ISSET(listenfd, &rset)) {
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
            
            for (i = 0; i < FD_SETSIZE; ++i) {
                if (client[i] < 0) {
                    client[i] = connfd;
                    break;
                }
            }
            
            if (i == FD_SETSIZE) {
                err_quit("too many clients");
            }
            
            FD_SET(connfd, &allset);
            if (connfd > maxfd) {
                maxfd = connfd;
            }
            if (i > maxi) {
                maxi = i;
            }
            if (--nready <= 0) {
                continue;
            }
        }
        
        for (i = 0; i <= maxi; ++i) {
            if ( (sockfd = client[i]) < 0) {
                continue;
            }
            
            if (FD_ISSET(sockfd, &rset)) {
                if ( (n = Read(sockfd, buf, MAXLINE)) == 0) {
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                } else {
                    Writen(sockfd, buf, n);
                }
                
                if (--nready <= 0) {
                    break;
                }
            }
        }
    }
}
