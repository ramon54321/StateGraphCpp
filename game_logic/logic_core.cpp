#include "logic_core.hpp"
#include <functional>

namespace game_logic
{
    LogicCore::LogicCore()
        : net_client_manager(
            std::bind(&LogicCore::on_message, this,
            std::placeholders::_1, std::placeholders::_2),
            std::bind(&LogicCore::on_connect, this,
            std::placeholders::_1),
            std::bind(&LogicCore::on_disconnect, this,
            std::placeholders::_1)
        ){}

    void LogicCore::send_message(unsigned int client_id, std::string message)
    {
        net_client_manager.send_message(client_id, message);
    }

    void LogicCore::on_message(unsigned int client_id, std::string message)
    {
        std::cout << "[LOGIC CORE] "
            << std::to_string(client_id)
            << " sent: "
            << message << std::endl;
    }

    void LogicCore::on_connect(unsigned int client_id)
    {
        std::cout << "[LOGIC CORE] " << std::to_string(client_id) 
            << " connected." 
            << std::endl;
    }

    void LogicCore::on_disconnect(unsigned int client_id)
    {
        std::cout << "[LOGIC CORE] " << std::to_string(client_id) 
            << " disconnected." 
            << std::endl;
    }
}