QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

INCLUDEPATH += $$PWD/../lib/
DEPENDPATH += $$PWD/../lib/

HEADERS += \
	../config.h \
    ../lib/addrinfo.h \
    ../lib/connect_nonb.lc \
    ../lib/connect_timeo.lc \
    ../lib/daemon_inetd.lc \
    ../lib/get_ifi_info.lc \
    ../lib/host_serv.lc \
    ../lib/mcast_join.lc \
    ../lib/mcast_set_loop.lc \
    ../lib/my_addrs.lc \
    ../lib/pselect.lc \
    ../lib/read_fd.lc \
    ../lib/readable_timeo.lc \
    ../lib/readline.lc \
    ../lib/readn.lc \
    ../lib/rtt.lc \
    ../lib/signal.lc \
    ../lib/sock_ntop.lc \
    ../lib/sockfd_to_family.lc \
    ../lib/str_cli.lc \
    ../lib/str_echo.lc \
    ../lib/tcp_connect.lc \
    ../lib/tcp_listen.lc \
    ../lib/udp_client.lc \
    ../lib/udp_connect.lc \
    ../lib/udp_server.lc \
    ../lib/unp.h \
    ../lib/unp.lh \
    ../lib/unpifi.h \
    ../lib/unprtt.h \
    ../lib/unprtt.lh \
    ../lib/unpthread.h \
    ../lib/wrappthread.lc \
    ../lib/wrapsock.lc \
    ../lib/write_fd.lc \
    ../lib/writen.lc \
    ../intro/daytimetcpsrv.lc

SOURCES += \
    ../lib/connect_nonb.c \
    ../lib/connect_timeo.c \
    ../lib/daemon_inetd.c \
    ../lib/daemon_init.c \
    ../lib/dg_cli.c \
    ../lib/dg_echo.c \
    ../lib/error.c \
    ../lib/family_to_level.c \
    ../lib/get_ifi_info.c \
    ../lib/gf_time.c \
    ../lib/host_serv.c \
    ../lib/hstrerror.c \
    ../lib/if_indextoname.c \
    ../lib/if_nameindex.c \
    ../lib/if_nametoindex.c \
    ../lib/in6addr_any.c \
    ../lib/mcast_get_if.c \
    ../lib/mcast_get_loop.c \
    ../lib/mcast_get_ttl.c \
    ../lib/mcast_join.c \
    ../lib/mcast_leave.c \
    ../lib/mcast_set_if.c \
    ../lib/mcast_set_loop.c \
    ../lib/mcast_set_ttl.c \
    ../lib/my_addrs.c \
    ../lib/pselect.c \
    ../lib/read_fd.c \
    ../lib/readable_timeo.c \
    ../lib/readline.c \
    ../lib/readn.c \
    ../lib/rtt.c \
    ../lib/signal_intr.c \
    ../lib/signal.c \
    ../lib/snprintf.c \
    ../lib/sock_bind_wild.c \
    ../lib/sock_cmp_addr.c \
    ../lib/sock_cmp_port.c \
    ../lib/sock_get_port.c \
    ../lib/sock_ntop_host.c \
    ../lib/sock_ntop.c \
    ../lib/sock_set_addr.c \
    ../lib/sock_set_port.c \
    ../lib/sock_set_wild.c \
    ../lib/sockatmark.c \
    ../lib/sockfd_to_family.c \
    ../lib/str_cli.c \
    ../lib/str_echo.c \
    ../lib/tcp_connect.c \
    ../lib/tcp_listen.c \
    ../lib/tv_sub.c \
    ../lib/udp_client.c \
    ../lib/udp_connect.c \
    ../lib/udp_server.c \
    ../lib/wraplib.c \
    ../lib/wrappthread.c \
    ../lib/wrapsock.c \
    ../lib/wrapstdio.c \
    ../lib/wrapunix.c \
    ../lib/writable_timeo.c \
    ../lib/write_fd.c \
    ../lib/writen.c \
    ../intro/byteorder.c \
    ../intro/daytimetcpcli.c \
    ../intro/daytimetcpcli1.c \
    ../intro/daytimetcpcli2.c \
    ../intro/daytimetcpcli3.c \
    ../intro/daytimetcpcliv6.c \
    ../intro/daytimetcpsrv.c \
    ../intro/daytimetcpsrv1.c \
    ../intro/daytimetcpsrv2.c \
    ../intro/daytimetcpsrv3.c \
    ../intro/daytimetcpsrvv6.c

DISTFILES += \
    ../lib/Makefile \
    ../intro/truss.solaris.2.6 \
    ../intro/truss.unixware.2.1 \
    ../intro/Makefile
