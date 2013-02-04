gcc ./client.c -o client -levent -lcrypto -lssl -ldl -lsqlite3 -ljansson -std=c99 `pkg-config --cflags --libs glib-2.0 gtk+-2.0 gnet-2.0` -Wall -Wextra -pedantic
