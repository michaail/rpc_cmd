/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "rpc_cmd.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

char * readBuff(FILE * stream)
{
    char buff[10];
    size_t cur_len = 0;
    size_t cur_max = 0;
    char *inputStd = NULL;

    while (fgets(buff, sizeof(buff), stream))
    {
        size_t buf_len = strlen(buff);
        if (cur_len + buf_len + 1 > cur_max)
        {
            size_t new_len = cur_max * 2 + 1;
            if (buf_len + 1 > new_len)
                new_len = buf_len + 1;
            char * extra = realloc(inputStd, new_len);
            if (extra == 0)
                break;
            inputStd = extra;
            cur_max = new_len;
        }
        strcpy(inputStd + cur_len, buff);
        cur_len += buf_len;
    }
    
    return inputStd;
}


cmdCallback * rcmd_1_svc(cmdParams *argp, struct svc_req *rqstp)
{
	static cmdCallback result;

    

    // Length of whole command + arguments to call
    int wholeLen = strlen(argp->command);
    for(int i = 0; i < argp->arguments.arguments_len; i++)
    {
        wholeLen = wholeLen + strlen(argp->arguments.arguments_val[i]) + 1;
    }
    //printf("debug: wholeLen passed [%d]\n", wholeLen);
    
    // Prepare whole cmd with arguments in one string
    char* cmd_ = malloc(wholeLen + 1);
    strcpy(cmd_, argp->command);
    strcat(cmd_, " ");
    for(size_t i = 0; i < argp->arguments.arguments_len; i++)
    {
        strcat(cmd_, argp->arguments.arguments_val[i]);
        strcat(cmd_, " ");
    }
    
    //printf("%s\n", cmd_);
    
    
    // command print Debug only
	//printf("%s %d\n", (char *)argp->command, argp->arguments.arguments_len);
	//printf("%s\n", argp->pipeData);

    // fd[0]: read end | fd[1]: write end
    int stdIn[2];   // stdin    descriptors
    int stdOut[2];  // stdout   descriptors
    int stdErr[2];  // stderr   descriptors

    // Create pipes for stdS (unidirectional data channels)
    

    // Tu się problem zaczyna
    if (pipe(stdIn) == -1) {
        perror("pipe");
    }
    
    //pipe(stdIn);
    pipe(stdOut);
    pipe(stdErr);
    

    int cpid = fork();
    if(cpid == 0)   // Child process
    {
        
        if (dup2(stdIn[0], STDIN_FILENO) == -1) {
            perror("dup2");
        }
        if (dup2(stdOut[1], STDOUT_FILENO) == -1) {
            perror("dup2");
        }
        if (dup2(stdErr[1], STDERR_FILENO) == -1) {
            perror("dup2");
        }
        
        //dup2(stdIn[0], STDIN_FILENO);
        //dup2(stdOut[1], STDOUT_FILENO);
        //dup2(stdErr[1], STDERR_FILENO);

        //printf("forked duped\n");
        close(stdIn[0]);
        close(stdOut[1]);
        close(stdErr[1]);

        // close(stdIn[1]);
        // close(stdOut[0]);
        // close(stdErr[0]);

        //printf("debug fork\n");
        // Cmd call in child process returns exit status
        int status = WEXITSTATUS(system(cmd_));
        //printf("%d\n", status);
        exit(status);
    }
    else            // Parent process
    {
        // Sets Nonblocking mode for streams
        close(stdIn[0]);
        close(stdOut[1]);
        close(stdErr[1]);
        // write from buffer to stream
        write(stdIn[1], argp->pipeData, strlen(argp->pipeData) + 1);
        close(stdIn[1]);
        //printf("to wait\n");

        // Dotąd proces macierzysty działa OK
        int sts;
        waitpid(cpid, &sts, 0);             // Wait for child process to change state
        result.stat = WEXITSTATUS(sts);     // returns exit status of child process

        fcntl(stdOut[0], F_SETFL, O_NONBLOCK);
        fcntl(stdErr[0], F_SETFL, O_NONBLOCK);

        char *inputStdOut, *inputStdErr;

        inputStdOut = readBuff(stdOut[0]);

        result.stdout = inputStdOut;

        inputStdErr = readBuff(stdErr[0]);

        result.stderr = inputStdErr;

        return &result;
    }

	// FILE *ls = popen("ls", "r");		// wywołanie komendy
	
    // odczyt printu komendy komendy
    // char buffer[10];
	// char *input = 0;
    // size_t cur_len = 0;
    // size_t cur_max = 0;

	// while (fgets(buffer, sizeof(buffer), ls) != 0)
    // {
    //     size_t buf_len = strlen(buffer);
    //     if (cur_len + buf_len + 1 > cur_max)
    //     {
    //         size_t new_len = cur_max * 2 + 1;
    //         if (buf_len + 1 > new_len)
    //             new_len = buf_len + 1;
    //         char *extra = realloc(input, new_len);
    //         if (extra == 0)
    //             break;
    //         input = extra;
    //         cur_max = new_len;
    //     }
    //     strcpy(input + cur_len, buffer);
    //     cur_len += buf_len;
    // }

    // printf("%s\n", input);

    // temp
    // char * err;
    // err = (char*)malloc(sizeof(char)* 1);

    // result.stderr = err;
    // result.stdout = input;
	// result.stat = 0;

	/*
	 * insert server code here
	 */

	
}
