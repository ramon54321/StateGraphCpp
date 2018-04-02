#include "net_client_manager.hpp"

using tcp = boost::asio::ip::tcp;

//------------------------------------------------------------------------------

namespace networking
{
    NetClientManager::NetClientManager()
    {
        client_manager_thread = new std::thread(&NetClientManager::listen, this);
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

                    // -- Add client to map
                    clients[client_id] = NetClient(this, client_id, socket);

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
        clients[client_id].send(message);
    }

    void NetClientManager::on_message(unsigned int client_id, std::string message)
    {
        std::cout << std::to_string(client_id) << ": " << message << std::endl;
    }
}