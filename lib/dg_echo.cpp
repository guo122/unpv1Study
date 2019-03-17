//
//  dg_echo.cpp
//  srvStudy
//
//  Created by John on 2019/3/16.
//  Copyright © 2019 John. All rights reserved.
//

#include "lib.h"

void
dg_echo (int sockfd, struct sockaddr * pcliaddr, socklen_t clilen) {
    int     n;
    socklen_t   len;
    char    mesg[MAXLINE];
    
    for (; ; ) {
        len = clilen;
        n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
        
        Sendto(sockfd, mesg, n, 0, pcliaddr, len);
    }
}
