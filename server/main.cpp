//  Created by Gusakov Nikita on 10/04/14.
//  Copyright (c) 2014 nkt. All rights reserved.

#include "Server.h"

int main()
{
    try {
        Server s("localhost", 4001, 256, true);
        s.run();
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    
}
