#include "session.h"

#include <iostream>
#include <boost/asio.hpp>

namespace io = boost::asio;
using tcp = io::ip::tcp;
using error_code = boost::system::error_code;

using namespace std::placeholders;

namespace {

uint64_t CalcHash(const io::const_buffer& buf, size_t len)
{
    using boost::asio::buffers_begin;

    // Polynomial rolling hash
    // https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/

    int prime = 31;
    int mod = 1e9 + 9;
    uint64_t primePow = 1;
    uint64_t res{};

    for (auto it = buffers_begin(buf); it != buffers_begin(buf) + len; it++)
    {
        res = (res + (*it - 'a' + 1) * primePow) % mod;
        primePow = (primePow * prime) % mod;
    }

    return res;
}

} // namespace

namespace hash_server {

Session::Session(tcp::socket&& socket)
    : m_socket(std::move(socket))
{
}

void Session::Start()
{
    std::cout << "Session started, socket: " << m_socket.native_handle() << std::endl;
    ReadAsync();
}

void Session::ReadAsync()
{
    io::async_read_until(m_socket, m_readBuf, "\n",
        std::bind(&Session::OnDataReceived, shared_from_this(), _1, _2));
}

void Session::WriteAsync()
{
    io::async_write(m_socket, m_writeBuf,
        std::bind(&Session::OnWriteCompleted, shared_from_this(), _1, _2));
}

void Session::OnDataReceived(error_code error, size_t len)
{
    using boost::asio::buffers_begin;

    if (error == io::error::eof)
    {
        std::cout << "session ended, socket: " << m_socket.native_handle() << std::endl;
        return;
    }

    if (error)
    {
        std::cout << "Session::OnDataReceived() failed, error: " << error.message() << std::endl;
        return;
    }

    uint64_t hash = CalcHash(m_readBuf.data(), len - 1);
    m_readBuf.consume(len);

    std::iostream stream(&m_writeBuf);
    stream << std::hex << hash << "\n";

    WriteAsync();
    ReadAsync();
}

void Session::OnWriteCompleted(boost::system::error_code error, std::size_t len)
{
    if (error)
    {
        std::cout << "Session::OnWriteCompleted() failed, error: " << error.message() << std::endl;
    }
}

} // namespace hash_server