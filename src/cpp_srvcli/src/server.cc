#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"


void add(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request>request, const std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response) {
	response->sum = request->a + request->b;
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incomming request\na: %ld b: %ld", request->a, request->b);
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "send back response: [%ld]", static_cast<long int>(response->sum));

}

int main(int argc, char* argv[]){
	rclcpp::init(argc, argv);
	auto node = rclcpp::Node::make_shared("add_two_ints_server");

	auto service = node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", &add);

	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");
	rclcpp::spin(node);
	rclcpp::shutdown();
	return EXIT_SUCCESS;
}
