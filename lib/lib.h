//
//  lib.h
//
//  Created by John on 2019/3/12.
//  Copyright © 2019 John. All rights reserved.
//

#ifndef unheader_h
#define unheader_h

#include    <stdlib.h>

#include    <netinet/in.h> /* sockaddr_in{} and other Internet defns */
#include    <arpa/inet.h>    /* inet(3) functions */
#include    <unistd.h>

#include    <errno.h>

#define     MAXLINE 4096

/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
 kernels still #define it as 5, while actually supporting many more */
#define     LISTENQ        1024    /* 2nd argument to listen() */

int         Socket(int, int, int);
void        Bind(int, const struct sockaddr *, socklen_t);
void        Listen(int, int);
void        Connect(int, const struct sockaddr *, socklen_t);
int         Accept(int, struct sockaddr *, socklen_t *);

void        Write(int, void *, size_t);
void        Close(int);

void        err_quit(const char *, ...);
void        err_sys(const char *, ...);

#endif /* unheader_h */
