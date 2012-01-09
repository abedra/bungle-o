#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "bungeloClient.h"
#include "bungeloServer.h"

static void printUsage(void) {
  printf("Usage: bungleo\n  -h, --help\n  -c, --client\n  -s, --server\n");
}

int main(int argc, char **argv)
{
  int client = 0;
  int server = 0;
  int option_index = 0;
  int c;
  
  while(1) {
    static struct option long_options[] = 
      {
	{"help",   no_argument, 0, 'h'},
	{"client", no_argument, 0, 'c'},
	{"server", no_argument, 0, 's'},
	{0, 0, 0, 0}
      };

    c = getopt_long(argc, argv, "hcs", long_options, &option_index);

    if(c == -1) break;

    switch(c)
      {
      case 'h':
        printUsage();
        return 0;
        break;
      case 'c':
        client = 1;
        break;
      case 's':
        server = 1;
        break;
      case '?':
        break;
      default:
        abort();
      }
  }
  
  if (client && server) {
    printUsage();
    return 1;
  } else if (!client && !server) {
    printUsage();
    return 1;
  } else if (server) {
    printf("Starting bungle-o server...\n");
    startBungeloClient();
  } else if (client) {
    printf("Starting bungle-o client...\n");
    startBungeloServer();
  } else {
    printUsage();
    return 1;
  }
  
  return 0;
}
