#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <boost/asio.hpp>
#include <array>
#include <cstdint>
#include <memory>
#include <mutex>

namespace net = boost::asio;
using udp = net::ip::udp;
using boost::system::error_code;

class UdpServer : public std::enable_shared_from_this<UdpServer>
{
public:
    UdpServer(net::io_context &ioc, uint16_t port);

    void start();
    void registerClient(uint32_t id, udp::endpoint ep);
    void unregisterClient(uint32_t id);
    void broadcastSnapshot();

private:
    void doReceive();

    udp::socket sock_;
    udp::endpoint sender_;
    std::array<uint8_t, 64> recv_{};
    std::mutex m_;
    std::unordered_map<uint32_t, udp::endpoint> clients_;
};

#endif

// socket
// mutex
// map
// callback