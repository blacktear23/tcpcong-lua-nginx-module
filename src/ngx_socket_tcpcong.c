
/*
 * Copyright (C) Rain Li
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include "ngx_socket_tcpcong.h"


#if (NGX_LINUX)

int
ngx_tcp_set_cong(ngx_socket_t s, const u_char* cong_name) {
    u_char optval[16];
    ngx_cpystrn(optval, (u_char *)cong_name, 15);
    return setsockopt(s, IPPROTO_TCP, TCP_CONGESTION,
                      (const void *)optval, strlen(optval));
}

#else

int
ngx_tcp_set_cong(ngx_socket_t s, const u_char* cong_name) {
    return 0;
}

#endif
