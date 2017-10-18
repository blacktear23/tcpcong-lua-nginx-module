# tcpcong-lua-nginx-module

tcpcong-lua-nginx-module is a openresty module to update connection’s TCP congestion control method.

## Usage

```
...

server {
    listen 80;

    location / {
        root html;
        index index.html index.htm;
        access_by_lua '
            local conn = require "ngx.conn"
            conn.set_cong("reno")
        ';
    }

    ...
}
```

## How to build by OpenResty

Update util/configure file:

```
...

my @modules = (
    ...
    [http_lua_tcpcong => 'tcpcong-lua-nginx-module'],
)

...
```

Copy `tcpcong-lua-nginx-module` directory to bundle directory and change name to: `tcpcong-lua-nginx-module-0.1`

```
# cp -r tcpcong-lua-nginx-module $openresty_dir/bundle
# mv $openresty_dir/bundle/tcpcong-lua-nginx-module $openresty_dir/bundle/tcpcong-lua-nginx-module-0.1
```
