#pragma once

#include <optional>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace hash_server {

class Server
{
public:

    explicit Server(boost::asio::io_context& io_context, std::uint16_t port);

    void Accept();

private:

    boost::asio::io_context& m_ioContext;
    boost::asio::ip::tcp::acceptor m_acceptor;
    std::optional<boost::asio::ip::tcp::socket> m_socket;
};

} // namespace hash_server