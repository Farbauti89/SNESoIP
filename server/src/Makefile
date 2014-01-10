# -*-makefile-*-
.PHONY: all clean


all:
	gcc -std=c99 -lconfig `mysql_config --cflags --libs` -o ../server \
	mysql.c protocol.c server.c

clean:
	rm ../server
