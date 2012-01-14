all: xml xpath

xml:
	gcc -o xml `xml2-config --cflags` xmlHandler.c `xml2-config --libs`

xpath:
	gcc -o xpath `xml2-config --cflags` xpathTest.c `xml2-config --libs`

clean:
	rm xml
	rm xpath
