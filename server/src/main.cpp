#include <boost/asio.hpp>
#include <cstdint>

#include "udp_server.h"
#include "tcp_session.h"

namespace net = boost::asio;
using tcp = net::ip::tcp;
//boost::system::error_code;

int main()
{
    uint16_t tcpPort = 9002, udpPort = 9003;


    net::io_context ioc;
    auto udp = std::make_shared<UdpServer>(ioc, udpPort);
    udp->start();

    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), tcpPort));
    std::function<void()> doAccept = [&]() {
        acceptor.async_accept([&](error_code ec, tcp::socket sock){
            if (!ec) {
                std::make_shared<TcpSession>(std::move(sock), *udp)->start();
            }
            doAccept();
        });
    };
    doAccept();
    return 0;
}