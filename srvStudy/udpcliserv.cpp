//
//  udpcliserv.cpp
//  srvStudy
//
//  Created by John on 2019/3/16.
//  Copyright © 2019 John. All rights reserved.
//

#include    "../lib/lib.h"

void
udpserv01() {
    PRINT_FUNC
    
    int     sockfd;
    struct  sockaddr_in servaddr, cliaddr;
    
    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    Bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    dg_echo(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
}
