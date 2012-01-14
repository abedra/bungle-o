#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <zmq.h>
#include <hiredis/hiredis.h>

static char * zrecv(void *socket) {
  int size;
  char *string;
  zmq_msg_t message;
  zmq_msg_init(&message);

  if(zmq_recv(socket, &message, 0)) return(NULL);

  size = zmq_msg_size(&message);
  string = malloc(size + 1);
  memcpy(string, zmq_msg_data(&message), size);
  zmq_msg_close(&message);
  string[size] = 0;
  return(string);
}

char *search(char *q, xmlDocPtr doc, xmlXPathContextPtr xpathCtx) {
  xmlNodeSetPtr nodes;
  xmlNodePtr cur;
  xmlXPathObjectPtr xpathObj;

  int i, size;
  char *result;

  xpathObj = xmlXPathEvalExpression(q, xpathCtx);
  if (xpathObj == NULL) {
    fprintf(stderr, "Error: unable to evaluate XPath expression\n");
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    return;
  }

  nodes = xpathObj->nodesetval;
  size = (nodes) ? nodes->nodeNr : 0;
  result = xmlNodeGetContent(nodes->nodeTab[0]);
  xmlXPathFreeObject(xpathObj);

  return result;
}

static int persist(redisContext *c, const char *key, const char *value) {
  redisReply *reply = redisCommand(c, "SADD %s %s", key, value);
  int response = reply->type;
  freeReplyObject(reply);
  return(response);
}

int main(void)
{
  redisContext *c;
  xmlDocPtr doc;
  xmlXPathContextPtr xpathCtx;

  void *context;
  void *receiver;
  char *errorXml;
  const char *id, *message;

  context = zmq_init(1);
  receiver = zmq_socket(context, ZMQ_PULL);
  zmq_connect(receiver, "tcp://localhost:5555");
  c = redisConnect("127.0.0.1", 6379);

  if(c->err) {
    printf("Error: %s\n", c->errstr);
    return 1;
  }

  while(1) {
    errorXml = zrecv(receiver);
    doc = xmlReadMemory(errorXml, strlen(errorXml), "noname.xml", NULL, 0);
 
   if (doc == NULL) {
      fprintf(stderr, "Error: unable to parse document\n");
      return 1;
    }

    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
      fprintf(stderr, "Error: unable to create new XPath context\n");
      xmlFreeDoc(doc);
      return 1;
    }

    id = search("/notice/api-key", doc, xpathCtx);
    message = search("/notice/error/message", doc, xpathCtx);

    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    persist(c, id, message);
  }

  redisFree(c);
  zmq_close(receiver);
  zmq_term(context);
  return 0;
}
