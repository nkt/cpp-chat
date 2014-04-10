//  Created by Gusakov Nikita on 10/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include <iostream>
#include "Client.h"

std::string messsager(std::string request)
{
    std::cout << request << std::endl;
    std::cin >> request;
    return request;
}

int main(int argc, const char * argv[])
{
    try {
        Client c("localhost", 7777);
        c.run(messsager);
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}

