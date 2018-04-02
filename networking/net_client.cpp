#include "net_client.hpp"

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

//------------------------------------------------------------------------------

NetClient::NetClient() {}

NetClient::NetClient(tcp::socket& socket)
{
    std::cout << "Creating client." << std::endl;
    websocket = new websocket::stream<tcp::socket>(std::move(socket));
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
            // This buffer will hold the incoming message
            boost::beast::multi_buffer buffer;

            // Read a message
            websocket->read(buffer);
            std::cout << "Got: " << buffers(buffer.data()) << std::endl;

            // Echo the message back
            websocket->text(websocket->got_text());
            websocket->write(buffer.data());
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