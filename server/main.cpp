//  Created by Gusakov Nikita on 10/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include "Server.h"

std::string messsager(std::string message)
{
    std::cout << message;
    std::cin >> message;
    return message;
}

int main()
{
    try {
        Server s("localhost", 7777);
        s.run(messsager);
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    
}
