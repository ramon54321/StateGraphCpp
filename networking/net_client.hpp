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
        // -- Manager of this client
        NetClientManager& net_client_manager;

        // -- Id in manager refering to this client
        unsigned int client_id;

        // -- Websocket to use to communicate with this client
        boost::beast::websocket::stream<tcp::socket>* websocket;

        // -- Thread listening for messages from this client
        std::thread client_thread;

    public:
        NetClient (
            NetClientManager& net_client_manager, unsigned int client_id,
            tcp::socket& socket
        );
        ~NetClient();

        // -- Listen for message from this client BLOCKING
        void listen();

        // -- Send message to client
        void send_message(std::string message);
    };
}