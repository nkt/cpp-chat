//  Created by Gusakov Nikita on 11/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include "SocketListener.h"

SocketListener::SocketListener(const char *host, const int port)
{
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        throw std::runtime_error(std::string("Could not open socket: ") + strerror(errno));
    }
    
    address = new sockaddr_in;
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    
    hostent *phe = gethostbyname(host);
    memcpy(&address->sin_addr, phe->h_addr, phe->h_length);
}

SocketListener::~SocketListener()
{
    shutdown(sock, SHUT_RDWR);
    close(sock);
}