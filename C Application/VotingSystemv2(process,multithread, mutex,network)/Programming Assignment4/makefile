make: all

all: server client

server: server.c util.h
	gcc -g -std=c99 -pthread -o server server.c

client: client.c util.h
	gcc -g -std=c99 -pthread -o client client.c

clean:
	rm server client
