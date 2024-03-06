#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from my_robot_interfaces.msg import HardwareStatus

class HWStatusPublisherNode(Node):
    def __init__(self):
        super().__init__('hw_status_publisher')
        self.hw_status_publisher_ = self.create_publisher(HardwareStatus, 'hardware_status', 10)
        self.timer_ = self.create_timer(0.5, self.publish_hw_status)
        
    def publish_hw_status(self):
        msg = HardwareStatus()
        msg.temperature = 45
        msg.are_motors_ready = True
        msg.debug_message = 'Everything is working fine'
        self.hw_status_publisher_.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.temperature)


def main(args=None):
    rclpy.init(args=args)
    node = HWStatusPublisherNode()
    rclpy.spin(node)
    rclpy.shutdown()
    
if __name__ == '__main__':
    main()