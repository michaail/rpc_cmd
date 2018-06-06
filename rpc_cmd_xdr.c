/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "rpc_cmd.h"

bool_t xdr_cmdCallback (XDR *xdrs, cmdCallback *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->stdout, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->stderr, ~0))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->stat))
		 return FALSE;
	return TRUE;
}

bool_t xdr_argument (XDR *xdrs, argument *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, objp, ~0))
		 return FALSE;
	return TRUE;
}

bool_t xdr_cmdParams (XDR *xdrs, cmdParams *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->command, ~0))
		 return FALSE;
	 if (!xdr_array (xdrs, (char **)&objp->arguments.arguments_val, (u_int *) &objp->arguments.arguments_len, ~0,
		sizeof (argument), (xdrproc_t) xdr_argument))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->pipeData, ~0))
		 return FALSE;
	return TRUE;
}
