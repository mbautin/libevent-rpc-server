// Following the tutorial at http://incpp.blogspot.com/2009/07/rpc-libevent.html


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>

#include "QueryTypes.gen.h"

#include <event2/event.h>
#include <event2/http.h>
#include <event2/rpc.h>
#include <event2/util.h>
#include <event2/buffer.h>

#include <sys/sysinfo.h>

EVRPC_HEADER(GetServerStat, StatRequest, StatReply);
EVRPC_GENERATE(GetServerStat, StatRequest, StatReply);

struct event_base* serv_base;
struct evrpc_base* rpc_base;
struct evhttp* http_base;
evutil_socket_t server_sock;

void GetServerStatCB(EVRPC_STRUCT(GetServerStat)* rpc, void *arg) {
  struct StatRequest * request = rpc->request;
  struct StatReply * reply = rpc->reply;

  struct sysinfo info;
  sysinfo(&info);

  if (EVTAG_HAS(request, uptime)) {
    char uptime_str[64];
    snprintf(uptime_str, sizeof(uptime_str) - 1, "%ld",  info.uptime);
    EVTAG_ASSIGN(reply, uptime, uptime_str);
  }
  EVRPC_REQUEST_DONE(rpc);
}

void generic_request_handler(struct evhttp_request *req, void *arg)
{
  struct evbuffer *returnbuffer = evbuffer_new();
  evbuffer_add_printf(returnbuffer, "Thanks for the request!");
  evhttp_send_reply(req, HTTP_OK, "Client", returnbuffer);
  evbuffer_free(returnbuffer);
}

void cleanup() {
  puts("Cleaning up");
  if (rpc_base != NULL) {
    EVRPC_UNREGISTER(rpc_base, GetServerStat);
    evrpc_free(rpc_base);
    rpc_base = NULL;
  }
  if (http_base != NULL) {
    evhttp_free(http_base);
    http_base = NULL;
  }
  if (server_sock != -1) {
    close(server_sock);
    server_sock = -1;
  }

}

void cleanup_callback(evutil_socket_t fd, short events, void * arg) {
  event_base_loopexit(serv_base, NULL);
}

int main(void) {

  serv_base = event_base_new();
  if (serv_base == NULL) {
    perror("event_base_new() failed");
    return EXIT_FAILURE;
  }

  server_sock = socket(AF_INET, SOCK_STREAM, 0);

  int reuseaddr_opt_val = 1;
  setsockopt(server_sock, SOL_SOCKET,SO_REUSEADDR, &reuseaddr_opt_val, sizeof(int));

  if (server_sock == -1) {
    perror("socket() failed");
    return EXIT_FAILURE;
  }
  if (evutil_make_socket_nonblocking(server_sock) < 0) {
    perror("evutil_make_socket_nonblocking() failed");
    return EXIT_FAILURE;
  }

  struct sockaddr_in sin;
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = 0;
  int port = 38123;
  sin.sin_port = htons(port);
  if (bind(server_sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
    perror("bind() failed");
    return EXIT_FAILURE;
  }
  if (listen(server_sock, 16)<0) {
    perror("listen() failed");
    return EXIT_FAILURE;
  }
  printf("Listening on port %d\n", port);

  http_base = evhttp_new(serv_base);

  if (evhttp_accept_socket(http_base, server_sock) == -1) {
    fputs("evhttp_accept_socket() failed", stderr);
    return EXIT_FAILURE;
  }

  rpc_base = evrpc_init(http_base);

  EVRPC_REGISTER(rpc_base, GetServerStat, StatRequest, StatReply, GetServerStatCB, NULL);
  evhttp_set_gencb(http_base, generic_request_handler, NULL);

  struct event* signal_event = event_new(serv_base, SIGINT, EV_SIGNAL | EV_PERSIST, cleanup_callback, NULL);
  event_add(signal_event, NULL);

  event_base_dispatch(serv_base);

  cleanup();
	return EXIT_SUCCESS;
}
