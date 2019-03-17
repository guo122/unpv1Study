//
//  dg_cli.cpp
//  srvStudy
//
//  Created by John on 2019/3/16.
//  Copyright © 2019 John. All rights reserved.
//

#include "lib.h"

void
dg_cli(FILE *fp, int sockfd, const struct sockaddr * pservaddr, socklen_t servlen) {
    int     n;
    char    sendline[MAXLINE], recvline[MAXLINE + 1];
    
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        
        n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        
        recvline[n] = 0;
        Fputs(recvline, stdout);
    }
}
