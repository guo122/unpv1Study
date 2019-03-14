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
str_cli1(FILE *fp, int sockfd)
{
    char    sendline[MAXLINE], recvline[MAXLINE];
    
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        
        Writen(sockfd, sendline, 1);
        
        sleep(1);
        
        Writen(sockfd, sendline + 1, strlen(sendline) - 1);
        
        if (Readline(sockfd, recvline, MAXLINE) == 0)
            err_quit("str_cli: server terminated prematurely");
        
        Fputs(recvline, stdout);
    }
}

void
str_cli09(FILE *fp, int sockfd)
{
    char    sendline[MAXLINE];
    struct args args;
    struct result result;
    
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        if (sscanf(sendline, "%ld%ld", &args.arg1, &args.arg2) != 2) {
            printf("invalid input: %s", sendline);
            continue;
        }
        
        Writen(sockfd, &args, sizeof(args));
        
        if (Readn(sockfd, &result, sizeof(result)) == 0) {
            err_quit("str_cli: server terminated prematurely");
        }
        printf("%ld\n", result.sum);
    }
}

#pragma mark -

void
tcpcli01(const char *addr_) {
    int sockfd;
    struct sockaddr_in servaddr;
    
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    
    Inet_pton(AF_INET, addr_, &servaddr.sin_addr);
    Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    str_cli(stdin, sockfd);
    
    exit(0);
}

void
tcpcli04(const char *addr_) {
    int i, sockfd[5];
    struct sockaddr_in servaddr;
    
    for (i = 0; i < 5; ++i) {
        sockfd[i] = Socket(AF_INET, SOCK_STREAM, 0);
        
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERV_PORT);
        
        Inet_pton(AF_INET, addr_, &servaddr.sin_addr);
        Connect(sockfd[i], (struct sockaddr *)&servaddr, sizeof(servaddr));
    }
    
    str_cli(stdin, sockfd[0]);
    
    exit(0);
}

void
tcpcli09(const char *addr_) {
    int sockfd;
    struct sockaddr_in servaddr;
    
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    
    Inet_pton(AF_INET, addr_, &servaddr.sin_addr);
    Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    str_cli09(stdin, sockfd);
    
    exit(0);
}
