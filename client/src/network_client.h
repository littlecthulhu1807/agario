#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H

#include <boost/asio.hpp>
#include <cstdint>
#include <thread>
#include <atomic>

#include "gameState.h"

namespace agario{

class NetworkClient{

public:
    NetworkClient(agario::GameState& state,
    const std::string& host = "127.0.0.1",
    uint16_t tcpPort = 9002,
    uint16_t udpPort = 9003);

    ~NetworkClient();

    void start();
    void stop();

private:
    void run();
    void sendPosition();
    void registerUdp();
    void doReadHeader();
    void doReadBody(uint8_t type, uint16_t len);

    boost::asio::io_context ioc_;
    boost::asio::ip::tcp::socket tcpSock_{ioc_};
    boost::asio::ip::udp::socket udpSock_{ioc_};

    GameState& state_;
    std::thread thread_;
    std::atomic<bool> running_{false};

    uint8_t hdr[3];
    std::vector<uint8_t> body_;
};


}



#endif