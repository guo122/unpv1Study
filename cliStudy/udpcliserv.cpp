//
//  udpcliserv.cpp
//  cliStudy
//
//  Created by John on 2019/3/16.
//  Copyright © 2019 John. All rights reserved.
//

#include "../lib/lib.h"

void
dg_cli_addr(FILE *fp, int sockfd, const struct sockaddr * pservaddr, socklen_t servlen) {
    int     n;
    char    sendline[MAXLINE], recvline[MAXLINE + 1];
    socklen_t len;
    struct sockaddr *preply_addr;
    
    preply_addr = static_cast<struct sockaddr *>(Malloc(servlen));
    
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        
        len = servlen;
        n = Recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);
        // todo sa_len不等，导致全被忽略
        if (len != servlen || memcmp(pservaddr, preply_addr, len) != 0) {
            printf("reply from %s (ignored)\n", Sock_ntop(preply_addr, len));
            continue;
        }
        
        recvline[n] = 0;
        Fputs(recvline, stdout);
    }
}

void
udpcli01(const char *addr_) {
    PRINT_FUNC
    
    int     sockfd;
    struct  sockaddr_in servaddr;
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, addr_, &servaddr.sin_addr);
    
    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    
    dg_cli(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
}

void
udpcliaddr(const char *addr_) {
    PRINT_FUNC
    
    int     sockfd;
    struct  sockaddr_in servaddr;
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, addr_, &servaddr.sin_addr);
    
    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    
    dg_cli_addr(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
}
