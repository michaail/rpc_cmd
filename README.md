## Usage
To run both server and client sides you need to have rpc protocol available on machine. You can check this by running:

    $ rpcinfo
If so to start the server type:

    $ sudo ./rpc_cmd_server
 Application can handle stdout, stdin and stderr of commands. To run client in general you need to:
 

    $ sudo ./rpc_cmd_client server_address command
e.g
 
    $ sudo ./rpc_cmd_client 127.0.0.1 ls
    $ sudo ./rpc_cmd_client 127.0.0.1 ps
You can also use pipe data and pass it to remotely executed command by simply

    $ echo "hello world" | sudo ./rpc_cmd_client 127.0.0.1 echo

 
