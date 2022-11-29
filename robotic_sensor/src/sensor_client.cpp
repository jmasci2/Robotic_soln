#include "rclcpp/rclcpp.hpp"
#include "robotic_sensor/srv/robotic_sensor.hpp"
#include "std_msgs/msg/string.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>
#include <functional>
#include <string>

#define  DATA_COUNT  0x31  //ascii 1

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class SensorPublisher : public rclcpp::Node
{
  public:
    SensorPublisher() : Node("sensor_publisher"), count_(0)
    {
      timer_cb_group_ = nullptr;
      client_ = this->create_client<robotic_sensor::srv::RoboticSensor>("sensor_data1", rmw_qos_profile_services_default,
                                                                client_cb_group_);

      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "SensorPublisher");
      publisher_ = this->create_publisher<std_msgs::msg::String>("sensors_data", 10);
      timer_ = this->create_wall_timer( 100ms, std::bind(&SensorPublisher::timer_callback, this), timer_cb_group_);
    }

  private:
    void timer_callback()
    {
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "timer_callback");
      auto request = std::make_shared<robotic_sensor::srv::RoboticSensor::Request>();
      request->sensordatapoints = DATA_COUNT;
      auto result_future = client_->async_send_request(request);
      std::future_status status = result_future.wait_for(200ms);  // timeout to guarantee a graceful finish
      if (status == std::future_status::ready) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "got response");
        auto message = std_msgs::msg::String();
        message.data = std::to_string(result_future.get()->sensordata[0]);
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Publishing: '%s'", message.data.c_str());
        publisher_->publish(message);
      }
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Client<robotic_sensor::srv::RoboticSensor>::SharedPtr client_;
    size_t count_;
    rclcpp::CallbackGroup::SharedPtr timer_cb_group_;
    rclcpp::CallbackGroup::SharedPtr client_cb_group_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  auto client_node = std::make_shared<SensorPublisher>();
  rclcpp::executors::MultiThreadedExecutor executor;
  executor.add_node(client_node);

  RCLCPP_INFO(client_node->get_logger(), "Starting client node, shut down with CTRL-C");
  executor.spin();
  RCLCPP_INFO(client_node->get_logger(), "Keyboard interrupt, shutting down.\n");

  rclcpp::shutdown();
  return 0;
}
