#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/msg/string.hpp>

class RobotNewsStation : public rclcpp::Node
{
public:
    RobotNewsStation() : Node("robot_news_station"), robot_name_("R2D2")
    {
        publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&RobotNewsStation::publish_news, this));
        count_ = 0;
        RCLCPP_INFO(this->get_logger(), "Robot News Station has been started.");
    }

private:
    void publish_news()
    {
        auto msg = example_interfaces::msg::String();
        msg.data = std::string("Hello, this is ") + robot_name_ + " from the robot news station " + std::to_string(count_++);
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", msg.data.c_str());
        publisher_->publish(msg);
    }

    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    size_t count_;
    std::string robot_name_;
};

int main(int argc, char **argv)
{
    // Initialize the ROS system and become a node.
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStation>();
    // Let the ROS run.
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}