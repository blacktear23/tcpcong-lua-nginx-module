
/*
 * Copyright (C) SpeedyCloud
 */

#ifndef _NGX_SOCKET_TCPCONG_H_INCLUDED_
#define _NGX_SOCKET_TCPCONG_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>

int ngx_tcp_set_cong(ngx_socket_t s, const u_char* cong_name);

#if (NGX_LINUX)

#ifndef TCP_CONGESTION
#define TCP_CONGESTION 13
#endif

#endif

#endif
