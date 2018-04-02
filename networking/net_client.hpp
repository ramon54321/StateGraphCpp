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

using tcp = boost::asio::ip::tcp;

//------------------------------------------------------------------------------

namespace networking
{
    class NetClientManager;

    class NetClient
    {
    private:
        NetClientManager* net_client_manager;
        unsigned int client_id;
        boost::beast::websocket::stream<tcp::socket>* websocket;
        std::thread* client_thread;

    public:
        NetClient();
        NetClient (NetClientManager* net_client_manager, unsigned int client_id,
            tcp::socket& socket);
        ~NetClient();

        // -- Listen for message from this client BLOCKING
        void listen();
        void send(std::string message);
    };
}