//
//  lib.h
//
//  Created by John on 2019/3/12.
//  Copyright © 2019 John. All rights reserved.
//

#ifndef unheader_h
#define unheader_h

#include    <iostream>
#include    <stdlib.h>

#include    <netinet/in.h> /* sockaddr_in{} and other Internet defns */
#include    <arpa/inet.h>    /* inet(3) functions */
#include    <unistd.h>

#include    <errno.h>

#define     MAXLINE 4096

/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
 kernels still #define it as 5, while actually supporting many more */
#define     LISTENQ        1024    /* 2nd argument to listen() */

/* Define some port number that can be used for our examples */
#define    SERV_PORT         9877            /* TCP and UDP */
#define    SERV_PORT_STR    "9877"            /* TCP and UDP */
#define    UNIXSTR_PATH    "/tmp/unix.str"    /* Unix domain stream */
#define    UNIXDG_PATH        "/tmp/unix.dg"    /* Unix domain datagram */
/* $$.ix [LISTENQ]~constant,~definition~of$$ */
/* $$.ix [MAXLINE]~constant,~definition~of$$ */
/* $$.ix [BUFFSIZE]~constant,~definition~of$$ */
/* $$.ix [SERV_PORT]~constant,~definition~of$$ */
/* $$.ix [UNIXSTR_PATH]~constant,~definition~of$$ */
/* $$.ix [UNIXDG_PATH]~constant,~definition~of$$ */

int         Socket(int, int, int);
void        Bind(int, const struct sockaddr *, socklen_t);
void        Listen(int, int);
void        Connect(int, const struct sockaddr *, socklen_t);
int         Accept(int, struct sockaddr *, socklen_t *);

void        Write(int, void *, size_t);
void        Close(int);
pid_t       Fork(void);

void        err_quit(const char *, ...);
void        err_sys(const char *, ...);

void        str_echo(int sockfd);
void        str_cli(FILE *, int);

ssize_t     writen(int, const void *, size_t);
void        Writen(int, void *, size_t);

const char * Inet_ntop(int, const void *, char *, size_t);
void        Inet_pton(int, const char *, void *);

void        Fputs(const char *, FILE *);
char *      Fgets(char *, int, FILE *);

ssize_t     Readline(int, void *, size_t);

#endif /* unheader_h */
