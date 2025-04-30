#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class MinimalSubscriber final: public rclcpp::Node {
public:
  MinimalSubscriber(): Node{"minimal_subscriber"} {
     subscription_ = create_subscription<std_msgs::msg::String>(
		    "topic",
		     10,
		     [this](const std_msgs::msg::String& msg) {
		    	this->topic_callback(msg); 
		     }); 
  }
private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;

  void topic_callback(const std_msgs::msg::String& msg) {
    RCLCPP_INFO(get_logger(), "I head: '%s'", msg.data.c_str());
  }
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return EXIT_SUCCESS;
}
