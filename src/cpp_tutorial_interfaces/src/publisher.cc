#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/msg/num.hpp"

class Publisher final: public rclcpp::Node {
public:
	Publisher(): Node{"talker"}, count_{0} {
		publisher_ = create_publisher<tutorial_interfaces::msg::Num>("topic", 10);
		using namespace std::chrono_literals;
		timer_ = create_wall_timer(500ms, 
				[this]() {
					this->timer_callback();	
				});


	}
private:
	void timer_callback() {
		auto msg = tutorial_interfaces::msg::Num();
		message.num = count_++; 
		RCLCPP_INFO_STREAM(get_logger(), "Publishing: '" << message.num << "'");
		publisher_->publish(message);
	}
	size_t count_;
	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Publisher<tutorial_interfaces::msg::Num>::SharedPtr publisher_;
};



int main(int argc, char*argv[]) {
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<Publisher>());
	rclcpp::shutdown();
	return EXIT_SUCCESS;
}
