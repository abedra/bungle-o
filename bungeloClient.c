#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>
#include "json/json.h"
#include "hiredis/hiredis.h"

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

static int persist(redisContext *c, const char *key, const char *value) {
  redisReply *reply = redisCommand(c, "SADD %s %s", key, value);
  int response = reply->type;
  freeReplyObject(reply);
  return(response);
}

int startBungeloClient(void)
{
  redisContext *c;
  void *context; 
  void *receiver;
  char *string;
  const char *id, *message;
  struct json_object *obj;

  context = zmq_init(1);
  receiver = zmq_socket(context, ZMQ_PULL);
  zmq_connect(receiver, "tcp://localhost:5555");
  c = redisConnect("127.0.0.1", 6379);

  if(c->err) {
    printf("Error: %s\n", c->errstr);
    return 1;
  }

  while(1) {
    string = zrecv(receiver);
    obj = json_tokener_parse(string);
    id = json_object_get_string(json_object_object_get(obj, "id"));
    message = json_object_get_string(json_object_object_get(obj, "message"));
    persist(c, id, message);
  }

  redisFree(c);
  zmq_close(receiver);
  zmq_term(context);
  return 0;
}
