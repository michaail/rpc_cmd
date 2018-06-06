/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _RPC_CMD_H_RPCGEN
#define _RPC_CMD_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct cmdCallback {
	char *stdout;
	char *stderr;
	int stat;
};
typedef struct cmdCallback cmdCallback;

typedef char *argument;

struct cmdParams {
	char *command;
	struct {
		u_int arguments_len;
		argument *arguments_val;
	} arguments;
	char *pipeData;
};
typedef struct cmdParams cmdParams;

#define RPC_CMD 0x20000000
#define V1 1

#if defined(__STDC__) || defined(__cplusplus)
#define rcmd 1
extern  cmdCallback * rcmd_1(cmdParams *, CLIENT *);
extern  cmdCallback * rcmd_1_svc(cmdParams *, struct svc_req *);
extern int rpc_cmd_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define rcmd 1
extern  cmdCallback * rcmd_1();
extern  cmdCallback * rcmd_1_svc();
extern int rpc_cmd_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_cmdCallback (XDR *, cmdCallback*);
extern  bool_t xdr_argument (XDR *, argument*);
extern  bool_t xdr_cmdParams (XDR *, cmdParams*);

#else /* K&R C */
extern bool_t xdr_cmdCallback ();
extern bool_t xdr_argument ();
extern bool_t xdr_cmdParams ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_RPC_CMD_H_RPCGEN */
