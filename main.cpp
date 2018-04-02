#include "networking/net_client.hpp"
#include "networking/net_client_manager.hpp"

//------------------------------------------------------------------------------

#include <chrono>

int main(int argc, char* argv[])
{
    NetClientManager netclman;
    std::cout << "Waiting..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}