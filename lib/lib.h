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

//#include    <sys/types.h>

#include    <netinet/in.h> /* sockaddr_in{} and other Internet defns */
#include    <arpa/inet.h>    /* inet(3) functions */
#include    <unistd.h>

typedef    void    Sigfunc(int);    /* for signal handlers */

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

#define    min(a,b)    ((a) < (b) ? (a) : (b))
#define    max(a,b)    ((a) > (b) ? (a) : (b))

#ifndef INFTIM
#define INFTIM          (-1)    /* infinite poll timeout */
/* $$.Ic INFTIM$$ */
#ifdef    HAVE_POLL_H
#define    INFTIM_UNPH                /* tell unpxti.h we defined it */
#endif
#endif

#define     PRINT_FUNC \
Fputs("--[", stdout);\
Fputs(__func__, stdout);\
Fputs("]--\n", stdout);

int         Socket(int, int, int);
void        Bind(int, const struct sockaddr *, socklen_t);
void        Listen(int, int);
void        Connect(int, const struct sockaddr *, socklen_t);
int         Accept(int, struct sockaddr *, socklen_t *);
int         Select(int, fd_set *, fd_set *, fd_set *,
                   struct timeval *);
void        Shutdown(int, int);
int         Poll(struct pollfd *, unsigned long, int);

void        Write(int, void *, size_t);
ssize_t     Read(int, void *, size_t);
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
ssize_t     Readn(int, void *, size_t);

Sigfunc *   Signal(int, Sigfunc *);

#endif /* unheader_h */
