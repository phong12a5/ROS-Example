#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/msg/string.hpp>

class SmartPhoneNode : public rclcpp::Node
{
public:
    SmartPhoneNode() : Node("smartphone_cpp")
    {
        subscription_ = this->create_subscription<example_interfaces::msg::String>(
            "robot_news", 10, std::bind(&SmartPhoneNode::callBackRobotNews, this, std::placeholders::_1));
    }

    private:
    void callBackRobotNews(const example_interfaces::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
    }

    rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    // Initialize the ROS system and become a node.
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SmartPhoneNode>();
    // Let the ROS run.
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}