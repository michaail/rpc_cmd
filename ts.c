#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char *argv[])
{
   
    FILE *ls = popen("ps -ax", "r");
    char buf[256];
    

    while (fgets(buf, sizeof(buf), ls) != 0)
    {

    }
    return 0;
}