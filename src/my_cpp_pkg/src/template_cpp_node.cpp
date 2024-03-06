#include <rclcpp/rclcpp.hpp>

class MyCustomeNode : public rclcpp::Node
{
public:
    MyNode() : Node("node_name")
    {
    }
};

int main(int argc, char **argv)
{
    // Initialize the ROS system and become a node.
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyCustomeNode>();
    // Let the ROS run.
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}