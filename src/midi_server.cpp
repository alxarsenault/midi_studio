#include "midi_server.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <asio/ts/buffer.hpp>

class session : public std::enable_shared_from_this<session> {
public:
  session(asio::ip::tcp::socket socket)
      : _socket(std::move(socket)) {}

  void start() { do_read(); }

private:
  void do_read() {
    auto self(shared_from_this());
    _socket.async_read_some(asio::buffer(_data, max_length), [this, self](std::error_code ec, std::size_t length) {
      (void)length;

      if (!ec) {
        do_read();
      }
    });
  }

  asio::ip::tcp::socket _socket;
  enum { max_length = 1024 };
  char _data[max_length];
};

MidiServer::MidiServer(short port)
    : _acceptor(_io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), (asio::ip::port_type)port))
    , _socket(_io_context) {}

MidiServer::~MidiServer() {
  _io_context.stop();
  _thread.join();
}

int MidiServer::start() {

  do_accept();

  _thread = std::thread([&]() { _io_context.run(); });
  return 0;
}

void MidiServer::do_accept() {
  _acceptor.async_accept(_socket, [this](std::error_code ec) {
    if (!ec) {
      std::make_shared<session>(std::move(_socket))->start();
    }

    do_accept();
  });
}
