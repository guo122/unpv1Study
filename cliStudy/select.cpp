//
//  select.cpp
//  cliStudy
//
//  Created by John on 2019/3/15.
//  Copyright © 2019 John. All rights reserved.
//

//#include <sys/select.h>
//#include <sys/time.h>

#include "../lib/lib.h"

void
str_cli_select01(FILE *fp, int sockfd)
{
    int     maxfdp1;
    fd_set  rset;
    char    sendline[MAXLINE], recvline[MAXLINE];
    
    FD_ZERO(&rset);
    
    for (; ; ) {
        FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        Select(maxfdp1, &rset, NULL, NULL, NULL);
        
        if (FD_ISSET(sockfd, &rset)) {
            if (Readline(sockfd, recvline, MAXLINE) == 0) {
                err_quit("str_cli: server terminated prematurely");
            }
            Fputs(recvline, stdout);
        }
        
        if (FD_ISSET(fileno(fp), &rset)) {
            if (Fgets(sendline, MAXLINE, fp) == NULL) {
                return;
            }
            Writen(sockfd, sendline, strlen(sendline));
        }
    }
}

void
str_cli_select02(FILE *fp, int sockfd)
{
    int     maxfdp1, stdineof;
    fd_set  rset;
    char    buf[MAXLINE];
    int     n;
    
    stdineof = 0;
    FD_ZERO(&rset);
    
    for (; ; ) {
        if (stdineof == 0) {
            FD_SET(fileno(fp), &rset);
        }
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        Select(maxfdp1, &rset, NULL, NULL, NULL);
        
        if (FD_ISSET(sockfd, &rset)) {
            if ( (n = Read(sockfd, buf, MAXLINE)) == 0) {
                if (stdineof == 1) {
                    return;
                }
                else {
                    err_quit("str_cli: server terminated prematurely");
                }
            }
            
            Write(fileno(stdout), buf, n);
        }
        
        if (FD_ISSET(fileno(fp), &rset)) {
            if ( (n = Read(fileno(fp), buf, MAXLINE)) == 0) {
                stdineof = 1;
                Shutdown(sockfd, SHUT_WR);
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            
            Writen(sockfd, buf, n);
        }
    }
}

#pragma mark -

void
tcpcliselect01(const char *addr_) {
    PRINT_FUNC
    
    int sockfd;
    struct sockaddr_in servaddr;
    
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    
    Inet_pton(AF_INET, addr_, &servaddr.sin_addr);
    Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    str_cli_select01(stdin, sockfd);
    
    exit(0);
}

void
tcpcliselect02(const char *addr_) {
    PRINT_FUNC
    
    int sockfd;
    struct sockaddr_in servaddr;
    
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    
    Inet_pton(AF_INET, addr_, &servaddr.sin_addr);
    Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    str_cli_select02(stdin, sockfd);
    
    exit(0);
}
