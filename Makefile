bungelo: 
	gcc bungeloClient.c bungeloServer.c bungelo.c -o bungelo -lzmq -lhiredis -ljson -ltofu

clean:
	rm bungelo
