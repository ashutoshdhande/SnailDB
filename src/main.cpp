#include <iostream>
#include <tcpServer.hpp>


int main(int argc, char const *argv[])
{
    Server server(1303);
    server.start();
    
    return 0;
}
