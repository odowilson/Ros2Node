#include "rclcpp/rclcpp.hpp"
#include "nav2_msgs/action/navigate_to_pose.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

void cancelAllGoals()
{
    // Create node
    auto node = rclcpp::Node::make_shared("navcancel");

    // Create NavigateToPose action client
    auto action_client = rclcpp_action::create_client<nav2_msgs::action::NavigateToPose>(node, "/navigate_to_pose");

    // Wait for the action server to become available
    while (!action_client->wait_for_action_server(std::chrono::seconds(1))) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(node->get_logger(), "Action server not available. Exiting.");
            rclcpp::shutdown();
            return;
        }
        RCLCPP_INFO(node->get_logger(), "Waiting for action server...");
    }

    // Cancel all goals
    auto future = action_client->async_cancel_all_goals();

    // Wait for the goals to be canceled
    while (rclcpp::ok() && std::future_status::ready != future.wait_for(std::chrono::seconds(1))) {
        RCLCPP_INFO(node->get_logger(), "Cancelling goals...");
        rclcpp::spin_some(node);
    }

    RCLCPP_INFO(node->get_logger(), "All goals canceled successfully.");
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    cancelAllGoals();

    rclcpp::shutdown();

    return 0;
}

