#include "net_client.hpp"
#include "net_client_manager.hpp"

using tcp = boost::asio::ip::tcp;

//------------------------------------------------------------------------------

namespace networking
{
    NetClient::NetClient() {}

    NetClient::NetClient(NetClientManager* net_client_manager,
        unsigned int client_id, tcp::socket& socket)
        : client_id(client_id)
    {
        std::cout << "Creating client." << std::endl;
        this->net_client_manager = net_client_manager;
        websocket = new boost::beast::websocket::stream<tcp::socket>(std::move(socket));
        client_thread = new std::thread(&NetClient::listen, this);
    }

    NetClient::~NetClient()
    {
        std::cout << "Deleting client." << std::endl;
    }

    void NetClient::listen()
    {
        try
        {
            // -- Accept the websocket handshake
            websocket->accept();

            // -- Loop process message
            while(true)
            {
                // -- Buffer to hold message
                boost::beast::multi_buffer buffer;

                // -- Read a message to buffer
                websocket->read(buffer);

                // -- Send message to net_client_manager
                net_client_manager->on_message(client_id,
                    boost::beast::buffers_to_string(buffer.data()));

                this->send("Thanks for the message: " + std::to_string(client_id));
            }
        }
        catch(boost::system::system_error const& session)
        {
            // -- This indicates that the session was closed
            std::cout << "Client disconnected" << std::endl;

            // -- If not a normal close -> Throw error
            if(session.code() != websocket::error::closed)
                std::cerr << "Error: " << session.code().message() << std::endl;
        }
        catch(std::exception const& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void NetClient::send(std::string message)
    {
        boost::beast::multi_buffer buffer;
        auto x = boost::asio::buffer_copy(buffer.prepare(message.size()),
            boost::asio::buffer(message));
        buffer.commit(x);
        websocket->write(buffer.data());
    }
}