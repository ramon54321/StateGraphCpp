#include "game_logic/logic_core.hpp"


//------------------------------------------------------------------------------

#include <chrono>

using game_logic::LogicCore;

int main(int argc, char* argv[])
{
    // -- Set up net_client_manager
    LogicCore logic_core;

    std::cout << "Waiting..." << std::endl;

    while(true)
    {
        std::string command;
        std::getline(std::cin, command);
        logic_core.send_message(0, command);
    }


    //std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}