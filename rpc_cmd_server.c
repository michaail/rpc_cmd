/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "rpc_cmd.h"

cmdCallback * rcmd_1_svc(cmdParams *argp, struct svc_req *rqstp)
{
	static cmdCallback result;



	printf("%s %d\n", (char *)argp->command, argp->arguments.arguments_len);
	
	printf("%s\n", argp->pipeData);

    
	FILE *ls = popen("ls", "r");		// wywołanie komendy
	
    // odczyt printu komendy komendy
    char buffer[10];
	char *input = 0;
    size_t cur_len = 0;
    size_t cur_max = 0;

	while (fgets(buffer, sizeof(buffer), ls) != 0)
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

    printf("%s\n", input);

    char * err;

    err = (char*)malloc(sizeof(char)* 1);

    result.stderr = err;
    result.stdout = input;
	result.stat = 0;

	/*
	 * insert server code here
	 */

	return &result;
}
