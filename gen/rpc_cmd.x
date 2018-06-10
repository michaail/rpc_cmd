struct cmdCallback{
    string stdout<>;
    string stderr<>;
    int stat;
};

typedef string argument<>;

struct cmdParams{
    string command<>;
    argument arguments<>;
    string pipeData<>;
};

program RPC_CMD {
    version V1{
        cmdCallback rcmd(cmdParams params) = 1;
    } = 1;
} = 0x20000000;