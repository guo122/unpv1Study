//
//  intro.cpp
//  cliStudy
//
//  Created by John on 2019/3/13.
//  Copyright © 2019 John. All rights reserved.
//

#include    "../lib/lib.h"

void
daytimetcpcli(const char * addr_) {
    PRINT_FUNC
    
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    
    //    if (argc != 2)
    //        err_quit("usage: a.out <IPaddress>");
    
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("connect error");
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    
    if (inet_pton(AF_INET, addr_, &servaddr.sin_addr) <= 0) {
        err_quit("inet_pton error for %s", addr_);
    }
    
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");
    
    while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF) {
            err_sys("fputs error");
        }
    }
    
    if (n < 0) {
        err_sys("read error");
    }
}
