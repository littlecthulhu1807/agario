#include <boost/asio.hpp>
#include <cstdint>
#include <iostream>
#include <csignal>

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

    std::cout << "Server running on Port:\n";
    std::cout << "\ttcpPort: " << tcpPort << "\n";
    std::cout << "\tudpPort: " << udpPort << "\n";

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

    // --- signal handling ---
    net::signal_set signals(ioc, SIGINT, SIGTERM);
    signals.async_wait([&](const boost::system::error_code& ec, int sig) {
        if (!ec) {
            std::cout << "\nReceived signal " << sig << ", shutting down...\n";
            ioc.stop();
        }
    });

    ioc.run();  // ← blocks here, dispatching all async handlers
    std::cout << "Server shutting down\n";
    return 0;
}