#include "net_client_manager.hpp"

using tcp = boost::asio::ip::tcp;
#include <functional>

//------------------------------------------------------------------------------

namespace networking
{
    NetClientManager::NetClientManager(
        // -- Link callback functions
        std::function<void(unsigned int, std::string)> on_message_callback,
        std::function<void(unsigned int)> on_connect_callback,
        std::function<void(unsigned int)> on_disconnect_callback)
        : on_message_callback(on_message_callback),
          on_connect_callback(on_connect_callback),
          on_disconnect_callback(on_disconnect_callback)

    {
        // -- Spin up new thread to listen for new connections
        client_manager_thread = new std::thread(&NetClientManager::listen, this);
    }

    NetClientManager::~NetClientManager()
    {
        // -- Delete thread
        delete client_manager_thread;
    }

    void NetClientManager::listen()
    {
        try
            {
                // -- The io_context is required for all I/O
                boost::asio::io_context io_contect(1);

                // -- Endpoint which will be connected to
                tcp::endpoint endpoint(tcp::v4(), 8080);

                // -- The acceptor receives incoming connections
                tcp::acceptor acceptor(io_contect, endpoint);

                while(true)
                {
                    // -- This will receive the new connection
                    tcp::socket socket{io_contect};

                    // -- Block until we get a connection
                    acceptor.accept(socket);

                    // -- Add client to map passing reference to this manager
                    clients[client_id] = new NetClient(*this, client_id, socket);

                    // -- Increment next client_id
                    client_id++;
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
    }

    void NetClientManager::send_message(unsigned int client_id, std::string message)
    {
        clients[client_id]->send_message(message);
    }

    void NetClientManager::on_message(unsigned int client_id, std::string message)
    {
        on_message_callback(client_id, message);
    }

    void NetClientManager::on_connect(unsigned int client_id)
    {
        on_connect_callback(client_id);
    }

    void NetClientManager::on_disconnect(unsigned int client_id)
    {
        on_disconnect_callback(client_id);
    }
}