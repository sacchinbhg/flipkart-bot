#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <ros/ros.h>
#include "rosserial_server/tcp_server.h"


int main(int argc, char* argv[])
{
  ros::init(argc, argv, "rosserial_server_socket_node4");
  int port;
  ros::param::param<int>("~port", port, 11414);
  boost::asio::io_service io_service;
  rosserial_server::TcpServer<> tcp_server(io_service, port);
  ROS_INFO_STREAM("Listening for rosserial TCP connections on port " << port);
  io_service.run();
  return 0;
}