#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

typedef struct {
  char *class;
  char *message;
  char *url;
  char *component;
  char *action;
  char *controller;
  char *projectRoot;
  char *environment;
  char *hostname;
} airbrakeException;

airbrakeException *read(const char *filename) {
  xmlDocPtr doc;
  xmlNodePtr cur;
  airbrakeException *e = malloc(sizeof(airbrakeException));

  doc = xmlParseFile(filename);

  if (doc == NULL) {
    fprintf(stderr, "Failed to parse %s\n", filename);
    return;
  }

  cur = xmlDocGetRootElement(doc);

  if (cur == NULL) {
    fprintf(stderr, "empty document\n");
    xmlFreeDoc(doc);
    return;
  }

  if (xmlStrcmp(cur->name, (const xmlChar*) "notice")) {
    fprintf(stderr, "wrong document type, root node != notice");
    xmlFreeDoc(doc);
    return;
  }

  cur = cur->xmlChildrenNode;
  while (cur != NULL) {
    if (!xmlStrcmp(cur->name, (const xmlChar *) "error")) {
      fprintf(stderr, "Found error node %s\n", cur->name);
    }
    cur = cur->next;
  }

  e->class = "ExceptionTest";
  e->message = "Message";

  xmlFreeDoc(doc);
  return e;
}

int main(int argc, char **argv) 
{
  airbrakeException *e;

  if (argc != 2) return 1;
  
  e = read(argv[1]);
  printf("Got error from class %s with message %s\n", e->class, e->message);

  if (e) free(e);
  xmlCleanupParser();
  xmlMemoryDump();

  return 0;
}
