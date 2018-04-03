#include "net_client.hpp"
#include "net_client_manager.hpp"

using tcp = boost::asio::ip::tcp;

//------------------------------------------------------------------------------

namespace networking
{
    NetClient::NetClient(
            // -- Reference to client manager
            NetClientManager& net_client_manager,

            // -- Reference to raw socket
            unsigned int client_id, tcp::socket& socket
        ):
            client_id(client_id),
            net_client_manager(net_client_manager),

            // -- Create new websocket from moved in raw socket
            websocket(
                new boost::beast::websocket
                    ::stream<tcp::socket>(std::move(socket))
            ),

            // -- Spin up a new thread to listen for messages from this client
            client_thread(std::thread(&NetClient::listen, this))
    {
        std::cout << "[NET CLIENT] Creating client." << std::endl;
    }

    NetClient::~NetClient()
    {
        std::cout << "[NET CLIENT] Deleting client." << std::endl;

        // -- Delete websocket
        delete websocket;

        // -- Detatch listening thread to allow for thread to quietly terminate
        client_thread.detach();
    }

    void NetClient::listen()
    {
        try
        {
            // -- Accept the websocket handshake
            websocket->accept();

            // -- Fire on_connect method in manager
            net_client_manager.on_connect(client_id);

            // -- Loop process message
            while(true)
            {
                // -- Buffer to hold message
                boost::beast::multi_buffer buffer;

                // -- Read a message to buffer
                websocket->read(buffer);

                // -- Send message to net_client_manager
                net_client_manager.on_message(client_id,
                    boost::beast::buffers_to_string(buffer.data()));

                this->send_message("Thanks for the message: " + std::to_string(client_id));
            }
        }
        catch(boost::system::system_error const& session)
        {
            // -- This indicates that the session was closed
            // -- Fire on_disconnect method in manager
            net_client_manager.on_disconnect(client_id);

            // -- If not a normal close -> Throw error
            if(session.code() != boost::beast::websocket::error::closed)
            {
                std::cerr << "Error: "
                << session.code().message()
                << std::endl;
            }
        }
        catch(std::exception const& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        delete this;
    }

    void NetClient::send_message(std::string message)
    {
        // -- Create buffer to store message in
        boost::beast::multi_buffer buffer;

        // -- Prepare buffer data
        auto x = boost::asio::buffer_copy(buffer.prepare(message.size()),
            boost::asio::buffer(message));

        // -- Commit data to buffer
        buffer.commit(x);

        // -- Write buffer data to websocket
        websocket->write(buffer.data());
    }
}