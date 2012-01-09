bungleo: 
	gcc -Wall -pedantic -Werror -O3 bungleoClient.c bungleoServer.c bungleo.c -o bungleo -lzmq -lhiredis -ljson -ltofu

clean:
	rm bungleo
