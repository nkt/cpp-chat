//  Created by Gusakov Nikita on 11/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include "SocketListener.h"

SocketListener::SocketListener(bool debug)
{
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        throw std::runtime_error("Could not open socket");
    } else if (debug) {
        std::cout << "Created socket" << std::endl;
    }
}

sockaddr *SocketListener::getAddressByHostname(const char *host, const int port)
{
    sockaddr_in *address = new sockaddr_in;
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    
    hostent *phe = gethostbyname(host);
    memcpy(&address->sin_addr, phe->h_addr, phe->h_length);
    
    return reinterpret_cast<sockaddr *>(address);
}

SocketListener::~SocketListener()
{
    shutdown(sock, SHUT_RDWR);
    close(sock);
}
