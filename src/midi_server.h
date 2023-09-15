#pragma once

#include <thread>
#include <asio/ts/internet.hpp>

class MidiServer {
public:
  MidiServer(short port);

  ~MidiServer();

  int start();

private:
  void do_accept();

  std::thread _thread;
  asio::io_context _io_context;
  asio::ip::tcp::acceptor _acceptor;
  asio::ip::tcp::socket _socket;
};
