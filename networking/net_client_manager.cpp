#include "net_client_manager.hpp"

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

//------------------------------------------------------------------------------

NetClientManager::NetClientManager()
{
    client_manager_thread = new std::thread(&NetClientManager::listen, this);
}

void NetClientManager::listen()
{
    try
        {
            // The io_context is required for all I/O
            boost::asio::io_context io_contect(1);

            // The acceptor receives incoming connections
            tcp::endpoint endpoint(tcp::v4(), 8080);
            tcp::acceptor acceptor(io_contect, endpoint);

            while(true)
            {
                // This will receive the new connection
                tcp::socket socket{io_contect};

                std::cout << "Waiting for connection request." << std::endl;
                // Block until we get a connection
                acceptor.accept(socket);


                clients[client_id] = NetClient(socket);
                client_id++;
                
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
}