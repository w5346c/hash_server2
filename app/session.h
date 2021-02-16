#pragma once

#include <memory>

#include <boost/system/error_code.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>

namespace hash_server {

class Session : public std::enable_shared_from_this<Session>
{
public:

    explicit Session(boost::asio::ip::tcp::socket&& socket);

    void Start();

private:

    void ReadAsync();
    void WriteAsync();
    void OnDataReceived(boost::system::error_code error, size_t len);
    void OnWriteCompleted(boost::system::error_code error, size_t len);

private:

    boost::asio::ip::tcp::socket m_socket;
    boost::asio::streambuf m_readBuf;
    boost::asio::streambuf m_writeBuf;
};

} // namespace hash_server