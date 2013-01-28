gcc ../src/server.c -o ../src/server -levent -lcrypto -lssl -ldl -lsqlite3 -ljansson -std=c99 `pkg-config --cflags --libs glib-2.0 gtk+-2.0 gnet-2.0`
