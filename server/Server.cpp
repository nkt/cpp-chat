//  Created by Gusakov Nikita on 10/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include "Server.h"

Server::Server(const char *host, const int port, const int connectionsLimit)
{
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        throw std::runtime_error("Could not open socket");
    }
    
    address = new sockaddr_in;
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    
    hostent *phe = gethostbyname(host);
    memcpy(&address->sin_addr, phe->h_addr, phe->h_length);
    
    if (bind(sock, reinterpret_cast<sockaddr *>(address), sizeof(sockaddr)) == -1) {
        throw std::runtime_error(std::string("Could not bind socket: ") + strerror(errno));
    }
    if (listen(sock, connectionsLimit) == -1) {
        throw std::runtime_error(std::string("Could not start listen new connections: ") + strerror(errno));
    }
}
void Server::run(std::string (*callback)(std::string message))
{
    int conn;
    char request[1024];
    std::string response;
    isRun = true;
    while (isRun) {
        conn = accept(sock, NULL, NULL);
        if (conn < 0) {
            close(sock);
            throw std::runtime_error(std::string("Could not accept new connection") + strerror(errno));
        }
        while (read(conn, &request, sizeof(request)) > 0) {
            response = callback(std::string(request));
            if (response.size() > 0) {
                write(conn, response.c_str(), response.size());
            }
        }
        shutdown(conn, SHUT_RDWR);
        close(sock);
    }
}
void Server::stop()
{
    isRun = false;
}