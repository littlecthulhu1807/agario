#include "tcp_session.h"

TcpSession::TcpSession(tcp::socket sock, UdpServer &udp)
    : sock_(std::move(sock)), udp_(udp)
{
}

void TcpSession::start()
{
    doReadHeader();
}

void TcpSession::close()
{
}

void TcpSession::doReadHeader()
{
    auto self = shared_from_this();
    net::async_read(
        sock_,
        net::buffer(hdr_, 3),
        [self](error_code ec, std::size_t)
        {
            if (ec)
            {
                self->close();
                return;
            }
            uint8_t type = self->hdr_[0];
            uint16_t len = self->hdr_[1] | (self->hdr_[2] << 8);
            self->doReadBody(type, len);
        });
}

void TcpSession::doReadBody(uint8_t type, uint16_t len)
{
    body_.resize(len);
    auto self = shared_from_this();
    net::async_read(
        sock_,
        net::buffer(body_),
        [self, type](error_code ec, std::size_t) {
            if (ec) 
            {
                self->close();
                return;
            }
            if (type == 1)
            {
                uint8_t out[4];
                // TODO: дописать потом
                net::write(self->sock_, net::buffer(out, 4));
            } else if (type == 2)
            {
                if (self->body_.size() >= 8)
                {
                    float x, y;
                    std::memcpy(&x, self->body_.data(), 4);
                    std::memcpy(&y, self->body_.data() + 4, 4);
                }
            }
            self->doReadHeader();
        }
    );

}