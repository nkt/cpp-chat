#include "Server.h"

using namespace std;

std::string messageCallback(std::string message)
{
    std::cout << message;
    std::cin >> message;
    return message;
}

int main()
{
    Server s("localhost", 7777);
    s.run(messageCallback);
}
