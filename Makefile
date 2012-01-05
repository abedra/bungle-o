all: server client

server:
	gcc -o server bungleo-server.c -lzmq -ltofu

client:
	gcc -o client bungleo-client.c -lzmq -ljson

clean:
	rm server
	rm client
