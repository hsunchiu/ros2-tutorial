#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/msg/num.hpp"


class Subscriber: public rclcpp::Node {
public:
	Subscriber(): Node{"subscriber"} {
		subscription_ = this->create_subscription<tutorial_interfaces::msg::Num>("topic",
		10, [this](const tutorial_interfaces::msg::Num& msg) {
			RCLCPP_INFO_STREAM(this->get_logger(), "I heard: '" << msg.num << "'");
		});		
	}

private:
	rclcpp::Subscription<tutorial_interfaces::msg::Num>::SharedPtr subscription_;
};


int main(int argc, char* argv[]) {
	rclcpp::init(argc, argv);

	rclcpp::spin(std::make_shared<Subscriber>());

	rclcpp::shutdown();

	return EXIT_SUCCESS;
}
