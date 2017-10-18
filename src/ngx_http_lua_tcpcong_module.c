
/*
 * Copyright (C) SpeedyCloud
 */


#include <ngx_core.h>
#include <ngx_http.h>
#include "ngx_http_lua_api.h"
#include "ngx_socket_tcpcong.h"


ngx_module_t ngx_http_lua_tcpcong_module;

static int ngx_http_lua_ngx_set_cong(lua_State *L);
static ngx_int_t ngx_http_lua_tcpcong_init(ngx_conf_t *cf);
static int ngx_http_lua_tcpcong_create_module(lua_State *L);


static ngx_http_module_t ngx_http_lua_tcpcong_ctx = {
    NULL,                           /* preconfiguration */
    ngx_http_lua_tcpcong_init,      /* postconfiguration */
    NULL,                           /* create main configuration */
    NULL,                           /* init main configuration */
    NULL,                           /* create server configuration */
    NULL,                           /* merge server configuration */
    NULL,                           /* create location configuration */
    NULL                            /* merge location configuration */
};

ngx_module_t ngx_http_lua_tcpcong_module = {
    NGX_MODULE_V1,
    &ngx_http_lua_tcpcong_ctx,   /* module context */
    NULL,                        /* module directives */
    NGX_HTTP_MODULE,             /* module type */
    NULL,                        /* init master */
    NULL,                        /* init module */
    NULL,                        /* init process */
    NULL,                        /* init thread */
    NULL,                        /* exit thread */
    NULL,                        /* exit process */
    NULL,                        /* exit master */
    NGX_MODULE_V1_PADDING
};

static ngx_int_t
ngx_http_lua_tcpcong_init(ngx_conf_t *cf)
{
    if (ngx_http_lua_add_package_preload(cf, "ngx.conn",
                                         ngx_http_lua_tcpcong_create_module)
        != NGX_OK)
    {
        return NGX_ERROR;
    }

    return NGX_OK;
}

static int
ngx_http_lua_tcpcong_create_module(lua_State * L)
{
    lua_createtable(L, 0, 1);

    lua_pushcfunction(L, ngx_http_lua_ngx_set_cong);
    lua_setfield(L, -2, "set_cong");

    return 1;
}


/**
 * Set TCP Congestion
 * */
static int
ngx_http_lua_ngx_set_cong(lua_State *L)
{
    ngx_http_request_t  *r;
    int                 nargs;
    int                 type;
    int                 ret;
    size_t              len;
    const char          *p;

    r = ngx_http_lua_get_request(L);
    if (r == NULL) {
        return luaL_error(L, "no request object found");
    }

    nargs = lua_gettop(L);
    if (nargs != 1) {
        return luaL_error(L, "attempt to pass %d arguments, bug accepted 1",
                          nargs);
    }
    type = lua_type(L, 1);
    if (type != LUA_TSTRING) {
        return luaL_error(L, "require string parameter");
    }
    p = lua_tolstring(L, 1, &len);
    ret = ngx_tcp_set_cong(r->connection->fd, (u_char *) p);
    if (ret < 0) {
        ngx_log_error(NGX_LOG_WARN, r->connection->log, 0,
                      "set tcp congestion %s failed: %d", p, ret);
    }
    return 1;
}
