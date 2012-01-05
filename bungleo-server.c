#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>
#include <tofu.h>

static int zsend (void *socket, char *string) {
  int rc;
  zmq_msg_t message;
  zmq_msg_init_size(&message, strlen(string));
  memcpy(zmq_msg_data(&message), string, strlen(string));
  rc = zmq_send(socket, &message, 0);
  zmq_msg_close(&message);
  return(rc);
}

tofu_rep_t *post(tofu_req_t *req, void *socket) {
  tofu_rep_t *rep = tofu_rep_init();
  int body_len;
  char *body = tofu_body(req, &body_len);

  zsend(socket, body);

  tofu_status(rep, 200);
  return rep;
}

int main() {
  char *opts[] = { "0.0.0.0", "5000" };
  tofu_ctx_t *ctx = tofu_ctx_init(TOFU_EVHTTP, opts);
  void *context = zmq_init(1);
  void *sender = zmq_socket(context, ZMQ_PUSH);
  zmq_bind(sender, "tcp://*:5555");

  tofu_handle_with(ctx, POST, "/", post, sender);
  tofu_loop(ctx);
  
  zmq_close(sender);
  zmq_term(context);
  tofu_ctx_free(ctx);
  return 0;
}
