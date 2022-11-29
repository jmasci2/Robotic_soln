#include "rclcpp/rclcpp.hpp"
#include "robotic_sensor/srv/robotic_sensor.hpp"

#include <memory>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 10000

int sock;

void get_data(const std::shared_ptr<robotic_sensor::srv::RoboticSensor::Request> request,
          std::shared_ptr<robotic_sensor::srv::RoboticSensor::Response> response)
{
  unsigned char outbuff[2];
  unsigned char inbuff[20];
  int valread;

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\ncount: %c" ,
                request->sensordatapoints);
  outbuff[0] = request->sensordatapoints;

  send(sock, outbuff, 1, 0);

  valread = read(sock, inbuff, 20);

  if (valread == request->sensordatapoints)
  {
    for (int i=0; i < valread; i++)
    {
      inbuff[i] = response->sensordata[i];
    }
  }
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%u]", inbuff[0]);
}

int main(int argc, char **argv)
{
  int client_fd;
  struct sockaddr_in serv_addr;

  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("sensor_data_server2");
  
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Socket creation error \n");
    return -1;
    }

  serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)	<= 0) {
	  printf("\nInvalid address/ Address not supported \n");
	  return -1;
	}

	if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) 	< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
 
  
  rclcpp::Service<robotic_sensor::srv::RoboticSensor>::SharedPtr service =
    node->create_service<robotic_sensor::srv::RoboticSensor>("sensor_data2", &get_data);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to send data.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}
