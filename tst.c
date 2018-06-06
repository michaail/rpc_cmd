#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

char * mal(FILE * desc)
{
    char buffer[10];
    char *input = 0;
    size_t cur_len = 0;
    size_t cur_max = 0;
    while (fgets(buffer, sizeof(buffer), desc) != 0)
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

    return input;
}


int main (int argc, char *argv[])
{

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
   
    char * inBuf = mal(stdin);

    //printf("%s\n", inBuf);

    FILE *ls = popen("cat", "r");

    fputs(inBuf, ls);

    char * buf = mal(ls);

    printf("%s [%d]", buf, (int)strlen(buf));
    free(buf);

    pclose(ls);

    
    return 0;
}