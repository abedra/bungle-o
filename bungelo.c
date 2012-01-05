#include <stdio.h>
#include <stdlib.h>
#include "bungeloClient.h"
#include "bungeloServer.h"

static void printUsage(void) {
  printf("Usage: bungelo [--client | --server]\n");
}

int main(int argc, char **argv)
{
  if(argc != 2) {
    printUsage();
    return 1;
  }

  char *mode = argv[1];

  if(strcmp(mode, "--client") == 0) {
    printf("Starting bungelo client...\n");
    startBungeloClient();
    } else if(strcmp(mode, "--server") == 0) {
    printf("Starting bungelo server...\n");
    startBungeloServer();
  } else {
    printf("Unknown option %s\n", mode);
    printUsage();
    return 2;
  }
}
