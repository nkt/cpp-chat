//  Created by Gusakov Nikita on 10/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#ifndef __chat__Server__
#define __chat__Server__

#include "SocketListener.h"
#include <iostream>
#include <string>
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>

class Server
{
private:
    int sock;
    bool isRun = false;
    bool debug;
    std::list<int> clients;
protected:
    static void *listenClients(void *arg);
    sockaddr *getAddressByHostname(const char *host, const int port);
public:
    Server(const char *host, const int port, const int connectionsLimit = 256, bool debug = false);
    void run();
    void stop();
};

#endif
