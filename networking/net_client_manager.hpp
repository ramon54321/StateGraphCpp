#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include "net_client.hpp"

//------------------------------------------------------------------------------

namespace networking
{
    class NetClient;

    class NetClientManager
    {
    private:
        std::thread* client_manager_thread;
        std::unordered_map<unsigned int, NetClient> clients;
        unsigned int client_id = 0;

    public:
        NetClientManager ();

        // -- Listen for new connections BLOCKING
        void listen();

        // -- Send message to client with given client_id
        void send_message(unsigned int client_id, std::string message);

        // -- Called when message is received by any client
        void on_message(unsigned int client_id, std::string message);
    };
}