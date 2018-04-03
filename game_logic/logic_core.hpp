#pragma once
#include "networking/net_client.hpp"
#include "networking/net_client_manager.hpp"
#include "state_management/state.hpp"
#include "game_logic/constants.hpp"
#include "game_logic/entity.hpp"
#include "game_logic/event_manager.hpp"

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

    class TeamTable
    {
    private:
        std::unordered_map<unsigned short,
            std::unordered_set<unsigned int>> client_by_team;
        std::unordered_map<unsigned int, unsigned short> team_by_client;

    public:
        void add_player(unsigned int client_id, unsigned short team_id)
        {
            client_by_team[team_id].insert(client_id);
            team_by_client[client_id] = team_id;
        }
        void remove_player(unsigned int client_id)
        {
            unsigned short team_id = team_by_client[client_id];
            team_by_client.erase(client_id);
            client_by_team[team_id].erase(client_id);
        }
        unsigned short get_player_team(unsigned int client_id)
        {
            return team_by_client[client_id];
        }
        const std::unordered_set<unsigned int>
            get_team_players(unsigned short team_id)
        {
            return client_by_team[team_id];
        }
    };

    class LogicCore
    {
    private:
        static LogicCore* instance;

        // -- Set up net_client_manager
        NetClientManager net_client_manager;

    public:
        // -- Set up team table
        TeamTable team_table;

    private:
        // -- Set up event manager
        EventManager event_manager;

        // -- Set up state for server
        State<unsigned int, StateVariableLabel, unsigned long, float> state;
    
    public:
        static LogicCore* getInstance(){ return instance; }

        LogicCore();
        
        /*
            NetClientManager

            These methods are used in conjunction with the net client manager.
            The net client manager is used to control network clients, in
            addition to calling the on_message method below when a client sends
            a message to the server.
        */
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