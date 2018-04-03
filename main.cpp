#include "game_logic/logic_core.hpp"
#include "game_logic/constants.hpp"
#include "game_logic/entity.hpp"
#include "game_logic/event_manager.hpp"

#include <iostream>
#include <chrono>

//------------------------------------------------------------------------------

using game_logic::LogicCore;

int main(int argc, char* argv[])
{

    // -- Set up logic
    LogicCore logic_core;

    std::cout << "Waiting..." << std::endl;

    while(true)
    {
        std::string command;
        std::getline(std::cin, command);
        //logic_core.send_message(0, command);

        if(command == "viewteams")
        {
            auto x = logic_core.team_table.get_team_players(0);
            for (auto player : x)
                std::cout << player << std::endl;

        }
    }

    //std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}