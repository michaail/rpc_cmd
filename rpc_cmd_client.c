/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "rpc_cmd.h"
#include <fcntl.h>
#include <unistd.h>


void rpc_cmd_1(char *host, char* cmd, int argsC, char** argument, char* pipeBuff)
{
	CLIENT *clnt;
	cmdCallback  *result_1;
	cmdParams  rcmd_1_arg;

	// przekazanie komendy do struktury
	rcmd_1_arg.arguments.arguments_len = argsC;		// liczba argumentów wywołania
	rcmd_1_arg.arguments.arguments_val = argument;	// wskaźnik na wartości argumentów
	rcmd_1_arg.command = cmd;						// komeda do wykonania
	rcmd_1_arg.pipeData = pipeBuff;					// wartość przechwyconego strumienia wejściowego | potok

#ifndef	DEBUG
	clnt = clnt_create (host, RPC_CMD, V1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = rcmd_1(&rcmd_1_arg, clnt);
	if (result_1 == (cmdCallback *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else
	{
		printf("%s\n", result_1->stdout);
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int main (int argc, char *argv[])
{
	char *host;

	if (argc < 3) {
		printf ("usage: %s server_host command\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

	char buffer[10];
    char *input = 0;
    size_t cur_len = 0;
    size_t cur_max = 0;
    while (fgets(buffer, sizeof(buffer), stdin) != 0)
    {
        size_t buf_len = strlen(buffer);
        if (cur_len + buf_len + 1 > cur_max)
        {
            size_t new_len = cur_max * 2 + 1;
            if (buf_len + 1 > new_len)
                new_len = buf_len + 1;
            char *extra = realloc(input, new_len);
            if (extra == 0)
                break;
            input = extra;
            cur_max = new_len;
        }
        strcpy(input + cur_len, buffer);
        cur_len += buf_len;
    }
	//input[cur_len] = 0;

    //printf("%s [%d]", input, (int)strlen(input));
    
	// 		   host; cmd;	  l.arg cmd; arg cmd; potok

	if (!input)
	{
		input = (char*)malloc(sizeof(char)* 1);
		printf("odczytu nie bylo\n");
	}

	rpc_cmd_1 (host, argv[2], argc - 3, argv + 3, input);

	free(input);

	exit (0);
}
