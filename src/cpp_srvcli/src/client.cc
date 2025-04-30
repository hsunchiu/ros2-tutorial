#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

#include <chrono>
#include <memory>
#include <cstdlib>


int main(int argc, char** argv) {
	rclcpp::init(argc, argv);

	if(argc != 3) {
		RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add_two_ints_client X Y");
		return EXIT_FAILURE;
	}

	auto node = rclcpp::Node::make_shared("add_two_ints_client");

	auto client = node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

	// construct the request
	auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
	request->a = atoll(argv[1]);
	request->b = atoll(argv[2]);

	using namespace std::chrono_literals;	// 1s for 1 second

	while(!client->wait_for_service(1s)) {
		if(!rclcpp::ok()) {
			RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
			return EXIT_FAILURE;			
		}
		RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
	}

	// the result' type is future type
	auto result = client->async_send_request(request);

	if(rclcpp::spin_until_future_complete(node, result) ==
		rclcpp::FutureReturnCode::SUCCESS) {
		RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->sum);
	} else {
		RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
	}

	rclcpp::shutdown();
	return EXIT_SUCCESS;
}
