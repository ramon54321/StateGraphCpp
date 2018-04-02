#include "networking/net_client.hpp"
#include "networking/net_client_manager.hpp"
#include "state_management/state.hpp"

//------------------------------------------------------------------------------

#include <chrono>

using namespace networking;
using state_management::State;

enum StateVariableLabel
{
    POSITION_X,
    POSITION_Y,
    POSITION_Z,
    MUNITIONS
};

int main(int argc, char* argv[])
{
    // -- Set up net_client_manager
    NetClientManager net_client_manager;

    // -- Set up state for server
    State<unsigned int, StateVariableLabel, unsigned long, float> state;


    std::cout << "Waiting..." << std::endl;

    while(true)
    {
        std::string command;
        std::getline(std::cin, command);
        net_client_manager.send_message(0, command);
    }


    //std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}