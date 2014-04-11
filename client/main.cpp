//  Created by Gusakov Nikita on 10/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include <iostream>
#include "Client.h"

int main(int argc, const char * argv[])
{
    try {
        Client c("localhost", 3333, true);
        c.run();
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}

