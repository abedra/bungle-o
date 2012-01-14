bungleo: 
	gcc -Wall -pedantic -Werror -O3 bungleoClient.c bungleoServer.c bungleo.c -o bungleo -lzmq -lhiredis -ljson -ltofu

airbrakeClient:
	gcc -o airbrakeClient `xml2-config --cflags` airbrakeClient.c `xml2-config --libs`

clean:
	rm bungleo
