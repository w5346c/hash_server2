#include "server.h"

#include <iostream>
#include <memory>

#include "session.h"

namespace io = boost::asio;
using tcp = io::ip::tcp;
using error_code = boost::system::error_code;

namespace hash_server {

Server::Server(io::io_context& io_context, std::uint16_t port)
    : m_ioContext(io_context)
    , m_acceptor(io_context, tcp::endpoint(io::ip::tcp::v4(), port))
{
    std::cout << "Starting hash server on port " << port << std::endl;
    Accept();
}

void Server::Accept()
{
    try
    {
        m_socket.emplace(m_ioContext);

        m_acceptor.async_accept(*m_socket, [this](error_code error)
            {
                std::make_shared<Session>(std::move(*m_socket))->Start();
                Accept();
            });
    }
    catch (std::exception& e)
    {
        std::cout << "Server::Accept(), error: " << e.what() << std::endl;
    }
}

} // namespace hash_server
