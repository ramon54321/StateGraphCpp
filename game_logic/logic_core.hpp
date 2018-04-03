#pragma once
#include "networking/net_client.hpp"
#include "networking/net_client_manager.hpp"
#include "state_management/state.hpp"

using networking::NetClientManager;
using state_management::State;

namespace game_logic
{
    enum StateVariableLabel
    {
        POSITION_X,
        POSITION_Y,
        ROTATION
    };

    class LogicCore
    {
    private:
        // -- Set up net_client_manager
        NetClientManager net_client_manager;

        // -- Set up state for server
        State<unsigned int, StateVariableLabel, unsigned long, float> state;
    
    public:
        LogicCore();
        
        // -- Send message to client with given client_id
        void send_message(unsigned int client_id, std::string message);

        // -- Called when message is received by any client
        void on_message(unsigned int client_id, std::string message);

        // -- Called when a client connects
        void on_connect(unsigned int client_id);

        // -- Called when a client disconnects
        void on_disconnect(unsigned int client_id);
    };
}