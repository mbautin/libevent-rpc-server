/*
 * Automatically generated from ./QueryTypes.rpc
 */

#ifndef EVENT_RPCOUT___QUERYTYPES_RPC_
#define EVENT_RPCOUT___QUERYTYPES_RPC_

#include <event2/util.h> /* for ev_uint*_t */
#include <event2/rpc.h>

struct StatRequest;
struct StatReply;

/* Tag definition for StatRequest */
enum statrequest_ {
  STATREQUEST_UPTIME=1,
  STATREQUEST_UNAME=2,
  STATREQUEST_MAX_TAGS
};

/* Structure declaration for StatRequest */
struct StatRequest_access_ {
  int (*uptime_assign)(struct StatRequest *, const ev_uint32_t);
  int (*uptime_get)(struct StatRequest *, ev_uint32_t *);
  int (*uname_assign)(struct StatRequest *, const ev_uint32_t);
  int (*uname_get)(struct StatRequest *, ev_uint32_t *);
};

struct StatRequest {
  struct StatRequest_access_ *base;

  ev_uint32_t uptime_data;
  ev_uint32_t uname_data;

  ev_uint8_t uptime_set;
  ev_uint8_t uname_set;
};

struct StatRequest *StatRequest_new(void);
struct StatRequest *StatRequest_new_with_arg(void *);
void StatRequest_free(struct StatRequest *);
void StatRequest_clear(struct StatRequest *);
void StatRequest_marshal(struct evbuffer *, const struct StatRequest *);
int StatRequest_unmarshal(struct StatRequest *, struct evbuffer *);
int StatRequest_complete(struct StatRequest *);
void evtag_marshal_StatRequest(struct evbuffer *, ev_uint32_t,
    const struct StatRequest *);
int evtag_unmarshal_StatRequest(struct evbuffer *, ev_uint32_t,
    struct StatRequest *);
int StatRequest_uptime_assign(struct StatRequest *, const ev_uint32_t);
int StatRequest_uptime_get(struct StatRequest *, ev_uint32_t *);
int StatRequest_uname_assign(struct StatRequest *, const ev_uint32_t);
int StatRequest_uname_get(struct StatRequest *, ev_uint32_t *);
/* --- StatRequest done --- */

/* Tag definition for StatReply */
enum statreply_ {
  STATREPLY_UPTIME=1,
  STATREPLY_UNAME=2,
  STATREPLY_MAX_TAGS
};

/* Structure declaration for StatReply */
struct StatReply_access_ {
  int (*uptime_assign)(struct StatReply *, const char *);
  int (*uptime_get)(struct StatReply *, char * *);
  int (*uname_assign)(struct StatReply *, const char *);
  int (*uname_get)(struct StatReply *, char * *);
};

struct StatReply {
  struct StatReply_access_ *base;

  char *uptime_data;
  char *uname_data;

  ev_uint8_t uptime_set;
  ev_uint8_t uname_set;
};

struct StatReply *StatReply_new(void);
struct StatReply *StatReply_new_with_arg(void *);
void StatReply_free(struct StatReply *);
void StatReply_clear(struct StatReply *);
void StatReply_marshal(struct evbuffer *, const struct StatReply *);
int StatReply_unmarshal(struct StatReply *, struct evbuffer *);
int StatReply_complete(struct StatReply *);
void evtag_marshal_StatReply(struct evbuffer *, ev_uint32_t,
    const struct StatReply *);
int evtag_unmarshal_StatReply(struct evbuffer *, ev_uint32_t,
    struct StatReply *);
int StatReply_uptime_assign(struct StatReply *, const char *);
int StatReply_uptime_get(struct StatReply *, char * *);
int StatReply_uname_assign(struct StatReply *, const char *);
int StatReply_uname_get(struct StatReply *, char * *);
/* --- StatReply done --- */

#endif  /* EVENT_RPCOUT___QUERYTYPES_RPC_ */
