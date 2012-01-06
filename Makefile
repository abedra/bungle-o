bungelo: 
	gcc -Wall -pedantic -Werror -O3 bungeloClient.c bungeloServer.c bungelo.c -o bungelo -lzmq -lhiredis -ljson -ltofu

clean:
	rm bungelo
