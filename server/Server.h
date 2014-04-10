//
//  Server.h
//  server
//
//  Created by Gusakov Nikita on 10/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.
//

#ifndef __nkt__Server__
#define __nkt__Server__

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string>

class Server {
private:
    int sock;
    sockaddr_in *address;
    bool isRun = false;
public:
    Server(const char *host, const int port, const int connectionsLimit = 256);
    void run(std::string (*callback)(std::string message));
    void stop();
};

#endif
