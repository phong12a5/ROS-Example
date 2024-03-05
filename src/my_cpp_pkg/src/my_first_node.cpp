#include <rclcpp/rclcpp.hpp>

class MyNode : public rclcpp::Node
{
public:
    MyNode() : Node("cpp_test")
    {
        RCLCPP_INFO(this->get_logger(), "Hello cpp node!");
        timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&MyNode::timer_callback, this));
    }

    void timer_callback()
    {
        counter_++;
        RCLCPP_INFO(this->get_logger(), "Hello %d", counter_);
    }

    private:
    rclcpp::TimerBase::SharedPtr timer_;
    int counter_;
};

int main(int argc, char **argv)
{
    // Initialize the ROS system and become a node.
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>();
    // Let the ROS run.
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}