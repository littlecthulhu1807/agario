#pragma once

#include <boost/asio.hpp>
#include <vector>

#include "udp_server.h"

namespace net = boost::asio;
using tcp = net::ip::tcp;

class TcpSession : public std::enable_shared_from_this<TcpSession>
{
public:
    TcpSession(tcp::socket sock, UdpServer &udp);
    void start();
    void close();

private:
    tcp::socket sock_;
    UdpServer &udp_;
    uint8_t hdr_[3]{};
    std::vector<uint8_t> body_;


    void doReadHeader();
    void doReadBody(uint8_t type, uint16_t len);
};