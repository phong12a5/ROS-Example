#include <rclcpp/rclcpp.hpp>
#include <my_robot_interfaces/msg/hardware_status.hpp>

class HWStatusPublisherNode : public rclcpp::Node
{
    public:
        HWStatusPublisherNode() : Node("hw_status_publisher_cpp")
        {
            publisher_ = this->create_publisher<my_robot_interfaces::msg::HardwareStatus>("hw_status", 10);
            timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&HWStatusPublisherNode::timer_callback, this));
        }

        void timer_callback()
        {
            auto msg = my_robot_interfaces::msg::HardwareStatus();
            msg.temperature = 57.2;
            msg.are_motors_ready = true;
            msg.debug_message = "All is running smoothly";
            publisher_->publish(msg);
            RCLCPP_INFO(this->get_logger(), "Publishing: '%ld'", msg.temperature);
        }

    private:
        rclcpp::Publisher<my_robot_interfaces::msg::HardwareStatus>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    // Initialize the ROS system and become a node.
    rclcpp::init(argc, argv);
    auto node = std::make_shared<HWStatusPublisherNode>();
    // Let the ROS run.
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}