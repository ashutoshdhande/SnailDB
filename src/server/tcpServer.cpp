#include <iostream>
#include <tcpServer.hpp>
// socket include files
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // for `sockaddr_in`
#include <arpa/inet.h>  // Provides functions like `inet_pton` and `inet_ntop`
#include <unistd.h>     // Provides `close` function for sockets
#include <netdb.h>      // for ni max host
#include <cstring>      // for memset

#include <json.hpp>
#include <StandardQuery.hpp>


Server::Server(int port)
{
    fileDescriptor = socket(AF_INET, SOCK_STREAM, 0); // IPv4 sequenced reliable stream with tcp
    if (fileDescriptor == -1)
    {
        std::cerr << "[ERROR] failed to create socket\n";
        exit(-1);
    }

    // 2. Bind the socket to a IP/Port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(1303); // make this read from a fileConfig
                                 // convert to ending little endian stuff on i3 9th gen it printed 1303 as 5893
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    if (bind(fileDescriptor, (struct sockaddr *)&hint, sizeof(hint)) == -1)
    {
        std::cerr << "[ERROR] failed to bind to socket\n";
        exit(-1);
    }
}

void Server::start()
{
    // 3. Make the socket listen
    if (listen(fileDescriptor, SOMAXCONN) == -1)
    {
        std::cerr << "[ERROR] failed to listen\n";
        exit(-1);
    }

    std::cout << "Server is ready and listening..." << std::endl;

    // 4. Accept a call
    while (true)
    {
        // Accept the incoming requests
        sockaddr_in client_address = {};
        socklen_t addressLen = sizeof(client_address);
        int connfd = accept(fileDescriptor, (struct sockaddr *)&client_address, &addressLen);
        if (connfd == -1)
        {
            std::cerr << "[ERROR] failed to connect to client\n";
            continue;
        }

        handleClient(connfd);
        // closing the client socket
        close(connfd);
    }

    // close the listening socket before exit
    close(fileDescriptor);
}

void Server::handleClient(int connfd)
{
    while (true)
    {
        // Here you would process a single request from the client
        char buffer[4096];
        memset(buffer, 0, 4096);

        // Read the client's message
        int bytesReceived = read(connfd, buffer, 4096);
        if (bytesReceived < 0)
        {
            std::cerr << "[ERROR] Failed to read from client\n";
            close(connfd); // Close the client socket
            continue;
        }
        // Parse json here
        std::string inputQuery(buffer, bytesReceived);
        /*
            have structure like
            {
                command: get | set | del
                key: well a key
                value: some datatypes (only set command will have value)
            }
         */
        nlohmann::json parsedQuery = nlohmann::json::parse(inputQuery);
        // i want to use that class here StandardQuery
        StandardQuery query(parsedQuery);

        // std::cout << "Command: " << parsedQuery.contains("command") << "\nKey: " << parsedQuery.contains("key") << "\nValue: " << parsedQuery.contains("value") << "\n";

        // std::cout<<parsedQuery["name"].get<std::string>()<<std::endl;
        // Create the response message "hy ${message}"
        std::string response = "hy";
        if(!query.getCommand().empty()){
            response.append(query.getCommand());
        }

         if(!query.getKey().empty()){
            response.append(query.getKey());
        }

        if(!query.getValue().empty()){
            response.append(query.getValue());
        }


        // Send the response back to the client
        send(connfd, response.c_str(), response.size(), 0);
    }
}