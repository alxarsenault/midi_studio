#include <iostream>
#include <asio.hpp>
#include <RtMidi.h>
#include <span>
#include <ctime>
#include <chrono>
#include <iostream>
#include <uv.h>
// A custom implementation of the Clock concept from the standard C++ library.
struct time_t_clock
{
  // The duration type.
  typedef std::chrono::steady_clock::duration duration;

  // The duration's underlying arithmetic representation.
  typedef duration::rep rep;

  // The ratio representing the duration's tick period.
  typedef duration::period period;

  // An absolute time point represented using the clock.
  typedef std::chrono::time_point<time_t_clock> time_point;

  // The clock is not monotonically increasing.
  static constexpr bool is_steady = false;

  // Get the current time.
  static time_point now() noexcept
  {
    return time_point() + std::chrono::seconds(std::time(0));
  }
};

// The asio::basic_waitable_timer template accepts an optional WaitTraits
// template parameter. The underlying time_t clock has one-second granularity,
// so these traits may be customised to reduce the latency between the clock
// ticking over and a wait operation's completion. When the timeout is near
// (less than one second away) we poll the clock more frequently to detect the
// time change closer to when it occurs. The user can select the appropriate
// trade off between accuracy and the increased CPU cost of polling. In extreme
// cases, a zero duration may be returned to make the timers as accurate as
// possible, albeit with 100% CPU usage.
struct time_t_wait_traits
{
  // Determine how long until the clock should be next polled to determine
  // whether the duration has elapsed.
  static time_t_clock::duration to_wait_duration(
      const time_t_clock::duration& d)
  {
    if (d > std::chrono::seconds(1))
      return d - std::chrono::seconds(1);
    else if (d > std::chrono::seconds(0))
      return std::chrono::milliseconds(10);
    else
      return std::chrono::seconds(0);
  }

  // Determine how long until the clock should be next polled to determine
  // whether the absoluate time has been reached.
  static time_t_clock::duration to_wait_duration(
      const time_t_clock::time_point& t)
  {
    return to_wait_duration(t - time_t_clock::now());
  }
};

typedef asio::basic_waitable_timer<
  time_t_clock, time_t_wait_traits> time_t_timer;
using asio::ip::tcp;

enum { max_length = 1024 };

static void MidiInputPortErrorCallback(RtMidiError::Type type, const std::string& errorText, void* userData) {
    (void)userData;
    std::cout << "ERROR " << errorText << " " << type << std::endl;
  }

  static void MidiInputPortCallback(double deltatime, std::vector<unsigned char>* message, void* userData) {
    (void)userData;

    if (!message) {
      return;
    }

    std::span<unsigned char> data(*message);
    if (data.empty()) {
      return;
    }

    if (data[0] == 0xF8) {
      //      std::cout << "Time Clock stamp = " << deltatime << std::endl;
      return;
    }

    for (size_t i = 0; i < data.size(); i++) {
      std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
    }

    std::cout << "stamp = " << deltatime << std::endl;
  }


class MidiClient
{
public:
  MidiClient(asio::io_context& io_context,
      const tcp::resolver::results_type& endpoints)
    : _io_context(io_context),
      _socket(io_context)
  {
    do_connect(endpoints);
  }

//  void write(const chat_message& msg)
//  {
//    asio::post(io_context_,
//        [this, msg]()
//        {
//          bool write_in_progress = !write_msgs_.empty();
//          write_msgs_.push_back(msg);
//          if (!write_in_progress)
//          {
//            do_write();
//          }
//        });
//  }

  void close()
  {
    asio::post(_io_context, [this]() { _socket.close(); });
  }

private:
  void do_connect(const tcp::resolver::results_type& endpoints)
  {
    asio::async_connect(_socket, endpoints,
        [this](std::error_code ec, tcp::endpoint)
        {
          if (!ec)
          {
            std::cout << "DSLKDJS" << std::endl;
            do_read_header();
          }
        });
  }

  void do_read_header()
  {
//    asio::async_read(socket_,
//        asio::buffer(read_msg_.data(), chat_message::header_length),
//        [this](std::error_code ec, std::size_t /*length*/)
//        {
//          if (!ec && read_msg_.decode_header())
//          {
//            do_read_body();
//          }
//          else
//          {
//            socket_.close();
//          }
//        });
  }

  void do_read_body()
  {
//    asio::async_read(socket_,
//        asio::buffer(read_msg_.body(), read_msg_.body_length()),
//        [this](std::error_code ec, std::size_t /*length*/)
//        {
//          if (!ec)
//          {
//            std::cout.write(read_msg_.body(), read_msg_.body_length());
//            std::cout << "\n";
//            do_read_header();
//          }
//          else
//          {
//            socket_.close();
//          }
//        });
  }

  void do_write()
  {
//    asio::async_write(socket_,
//        asio::buffer(write_msgs_.front().data(),
//          write_msgs_.front().length()),
//        [this](std::error_code ec, std::size_t /*length*/)
//        {
//          if (!ec)
//          {
//            write_msgs_.pop_front();
//            if (!write_msgs_.empty())
//            {
//              do_write();
//            }
//          }
//          else
//          {
//            socket_.close();
//          }
//        });
  }

private:
  asio::io_context& _io_context;
  tcp::socket _socket;
//  chat_message read_msg_;
//  chat_message_queue write_msgs_;
};

void wait_for_a_while(uv_idle_t* handle) {
  std::cout << "DSLDKJ " << handle->data << std::endl;
//    counter++;
//
//    if (counter >= 10e6)
//        uv_idle_stop(handle);
}



static void alloc_cb(uv_handle_t* handle, size_t size, uv_buf_t* buf) {
  *buf = uv_buf_init((char*)malloc(size), size);
}

void on_close(uv_handle_t* handle)
{
  printf("closed.");
}

void on_write(uv_write_t* req, int status)
{
  if (status) {
    perror( "uv_write error ");
        return;
  }
    printf("wrote.\n");
    free(req);
    //uv_close((uv_handle_t*)req->handle, on_close);
}

void write2(uv_stream_t* stream, char *data, int len2) {
    uv_buf_t buffer[] = {
         data, (size_t)len2
    };
    uv_write_t *req = (uv_write_t*)malloc(sizeof(uv_write_t));
    uv_write(req, stream, buffer, 1, on_write);
}

void on_connect(uv_connect_t* connection, int status)
{
    if (status < 0) {
        printf("failed to connect\n"); return;
    }
    printf("connected. %p %d\n",connection, status);

    uv_stream_t* stream = connection->handle;
//    free(connection);
    write2(stream, "echo  world!", 12);
  
  
//    uv_read_start(stream, alloc_cb, on_read);
}
void vvv(uv_timer_t* handle) {
  std::cout << "DSLDKJ " << handle->data << std::endl;

}
int main(int argc, char* argv[])
{
  RtMidiIn midi(RtMidi::Api::MACOSX_CORE, "MIDI Studio");
  midi.openVirtualPort("MIDI Studio");
  midi.setCallback(&MidiInputPortCallback, nullptr);
  midi.setErrorCallback(&MidiInputPortErrorCallback, nullptr);
  midi.ignoreTypes(false, false, false);
  
  
  uv_loop_t* loop =uv_default_loop();
  
  
  uv_timer_t timer;
  uv_timer_init(loop, &timer);
  uv_timer_start(&timer, &vvv, 200, 1);
  
//  UV_EXTERN int uv_timer_init(uv_loop_t*, uv_timer_t* handle);
//  UV_EXTERN int uv_timer_start(uv_timer_t* handle,
//                               uv_timer_cb cb,
//                               uint64_t timeout,
//                               uint64_t repeat);
//
//  uv_idle_t idler;
//  idler.data = (void*)&midi;
//  
//      uv_idle_init(loop, &idler);
//      uv_idle_start(&idler, wait_for_a_while);

  struct sockaddr_in addr;
  uv_tcp_t socket;
      uv_tcp_init(loop, &socket);

      uv_ip4_addr("10.0.0.221", 8910, &addr);

  uv_connect_t con;
//     printf("allocated %p\n", pConn);
     uv_tcp_connect(&con, &socket, (const struct sockaddr*)&addr, on_connect);
  
  
  
      printf("Idling...\n");
      uv_run(loop, UV_RUN_DEFAULT);

      uv_loop_close(loop);
  
//  std::vector<unsigned char> message;
//
//  try
//  {
//    if (argc != 3)
//    {
//      std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
//      return 1;
//    }
//
//    asio::io_context io_context;
//
//    time_t_timer timer(io_context);
//
//
//    tcp::resolver resolver(io_context);
//    auto endpoints = resolver.resolve(argv[1], argv[2]);
//    MidiClient c(io_context, endpoints);
//
//    timer.expires_after(std::chrono::seconds(5));
//    timer.async_wait(
//            [](const std::error_code& /*error*/)
//            {
//              std::cout << "timeout\n";
//            });
//
//    io_context.run();
////    tcp::socket s(io_context);
////    tcp::resolver resolver(io_context);
////    asio::connect(s, resolver.resolve(argv[1], argv[2]));
////
////    std::cout << "Enter message: ";
////    char request[max_length];
////    std::cin.getline(request, max_length);
////    size_t request_length = std::strlen(request);
////    asio::write(s, asio::buffer(request, request_length));
//
////    char reply[max_length];
////    size_t reply_length = asio::read(s,
////        asio::buffer(reply, request_length));
////    std::cout << "Reply is: ";
////    std::cout.write(reply, reply_length);
////    std::cout << "\n";
//  }
//  catch (std::exception& e)
//  {
//    std::cerr << "Exception: " << e.what() << "\n";
//  }

  return 0;
}
