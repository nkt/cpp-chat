//  Created by Gusakov Nikita on 10/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include "Server.h"

Server::Server(const char *host, const int port, const int connectionsLimit, bool _debug) : debug(_debug)
{
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        throw std::runtime_error("Could not open socket");
    } else if (debug) {
        std::cout << "Created socket" << std::endl;
    }
    if (bind(sock, getAddressByHostname(host, port), sizeof(sockaddr)) == -1) {
        throw std::runtime_error(std::string("Could not bind socket: ") + strerror(errno));
    } else if (debug) {
        std::cout << "Binded socket on " << host << ":" << port << std::endl;
    }
    
    if (listen(sock, connectionsLimit) == -1) {
        throw std::runtime_error(std::string("Could not start listen new connections: ") + strerror(errno));
    } else if (debug) {
        std::cout << "Start listening socket. Max: " << connectionsLimit << std::endl;
    }
}

sockaddr *Server::getAddressByHostname(const char *host, const int port)
{
    sockaddr_in *address = new sockaddr_in;
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    
    hostent *phe = gethostbyname(host);
    memcpy(&address->sin_addr, phe->h_addr, phe->h_length);
    
    return reinterpret_cast<sockaddr *>(address);
}

void *Server::listenClients(void *arg)
{
    Server *s = static_cast<Server *>(arg);
    char message[1024];
    while (s->isRun) {
        for (int sender : s->clients) {
            if (read(sender, &message, sizeof(message)) > 0) {
                for (int listener : s->clients) {
                    if (listener != sender) {
                        write(listener, message, sizeof(message));
                    }
                }
            }
        }
        usleep(100);
    }
    for (int conn : s->clients) {
        shutdown(conn, SHUT_RDWR);
        close(conn);
    }
    
    return NULL;
}

void Server::run()
{
    pthread_t listenerThread;
    if (pthread_create(&listenerThread, NULL, &Server::listenClients, &*this) != 0){
        throw std::runtime_error(std::string("Could not create listener thread: ") + strerror(errno));
    } else if (debug) {
        std::cout << "Created listener thread" << std::endl;
    }
    isRun = true;
    int conn;
    while (isRun) {
        conn = accept(sock, NULL, NULL);
        if (conn < 0) {
            close(sock);
            throw std::runtime_error(std::string("Could not accept new connection: ") + strerror(errno));
        } else if (debug) {
            std::cout << "Accepted new connection!" << std::endl;
        }
        clients.push_back(conn);
    }
    shutdown(sock, SHUT_RDWR);
    close(sock);
}
void Server::stop()
{
    isRun = false;
}