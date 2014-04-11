//  Created by Gusakov Nikita on 10/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include "Client.h"

Client::Client (const char *host, const int port, bool debug) : SocketListener(debug)
{
    if (connect(sock, getAddressByHostname(host, port), sizeof(sockaddr)) == -1) {
        throw std::runtime_error(std::string("Could not open connection: ") + strerror(errno));
    } else if (debug) {
        std::cout << "Connected to " << host << ":" << port << std::endl;
    }
}

void *Client::messager(void *arg)
{
    char message[1024];
    
    Client *client = (Client *)arg;
    
    for (;;usleep(50)) {
        std::cout << "> ";
        std::cin.getline(message, 1024);
        if (write(client->sock, message, sizeof(message)) < 0) {
            if (client->debug) {
                std::cout << "Connection lost" << std::endl;
            }
            break;
        }
    }
    
    return NULL;
}

void Client::run()
{
    char message[1024];
    isRun = true;
    pthread_t messagerThread;
    pthread_create(&messagerThread, NULL, &Client::messager, &*this);
    while (isRun && read(sock, &message, sizeof(message)) > 0) {
        std::cout << message << std::endl;
    }
    if (debug) {
        std::cout << "Connection lost" << std::endl;
    }
}

void Client::stop()
{
    isRun = false;
}