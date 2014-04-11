//  Created by Gusakov Nikita on 10/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#ifndef __chat__Client__
#define __chat__Client__

#include "SocketListener.h"
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>

class Client : SocketListener
{
private:
    bool isRun = false;
    bool debug;
public:
    Client(const char *host, const int port, bool debug = false);
    void run();
    void stop();
    static void *messager(void *arg);
};

#endif
