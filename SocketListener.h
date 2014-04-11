//  Created by Gusakov Nikita on 11/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#ifndef __chat__SocketListener__
#define __chat__SocketListener__

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string>

class SocketListener
{
protected:
    int sock;
    sockaddr *getAddressByHostname(const char *host, const int port);
public:
    SocketListener(bool debug);
    ~SocketListener();
};

#endif