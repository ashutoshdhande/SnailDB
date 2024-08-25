#ifndef SNAILDB_TCP_SERVER_H
#define SNAILDB_TCP_SERVER_H

#include <netinet/in.h>      // for `sockaddr_in`

class Server {
    public:
        Server(int port);
        void start();
    private:
        int fileDescriptor;
        sockaddr_in hint;
        void handleClient(int client_socket);
};

#endif