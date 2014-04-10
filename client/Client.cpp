//  Created by Gusakov Nikita on 10/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include "Client.h"

Client::Client (const char *host, const int port) : SocketListener(host, port)
{
    if(connect(sock, reinterpret_cast<sockaddr *>(address), sizeof(sockaddr)) == -1) {
        throw std::runtime_error(std::string("Could not open connection") + strerror(errno));
    }
}

void Client::run(std::string (*callback)(std::string message))
{
    char request[1024];
    std::string response;
    isRun = true;
    while (isRun && recv(sock, &request, sizeof(request), NULL) > 0) {
        response = callback(std::string(request));
        if (response.size() > 0) {
            send(sock, response.c_str(), response.size(), NULL);
        }
    }
}
void Client::stop()
{
    isRun = false;
}