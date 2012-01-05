#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>
#include "json/json.h"
#include "hiredis/hiredis.h"

static char * zrecv(void *socket) {
  zmq_msg_t message;
  zmq_msg_init(&message);
  
  if(zmq_recv(socket, &message, 0)) return(NULL);
  
  int size = zmq_msg_size(&message);
  char *string = malloc(size + 1);
  memcpy(string, zmq_msg_data(&message), size);
  zmq_msg_close(&message);
  string[size] = 0;
  return(string);
}

static int persist(redisContext *c, const char *key, const char *value) {
  redisReply *reply = redisCommand(c, "SET %s %s", key, value);
  int response = reply->type;
  freeReplyObject(reply);
  return(response);
}

int main(void)
{
  void *context = zmq_init(1);
  void *receiver = zmq_socket(context, ZMQ_PULL);
  zmq_connect(receiver, "tcp://localhost:5555");
  
  redisContext *c = redisConnect("127.0.0.1", 6379);
  if(c->err) {
    printf("Error: %s\n", c->errstr);
    return 1;
  }

  const char *id, *message;
  char *string;
  struct json_object *obj;

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
