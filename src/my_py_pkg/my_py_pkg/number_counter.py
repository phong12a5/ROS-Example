#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import Int64

class NumberCounter(Node):
    def __init__(self):
        super().__init__('number_counter')
        self.counter = 0
        self.publishers_ = self.create_publisher(Int64, 'number_count', 10)
        self.subscriptions_ = self.create_subscription(Int64, 'number', self.number_callback, 10)

    def number_callback(self, msg):
        self.get_logger().info('I heard: "%d"' % msg.data)
        self.counter += msg.data
        count = Int64()
        count.data = self.counter
        self.publishers_.publish(count)
        self.get_logger().info('I published: "%d"' % count.data)

def main(args=None):
    rclpy.init(args=args)
    node = NumberCounter()
    rclpy.spin(node)
    rclpy.shutdown()
    
if __name__ == '__main__':
    main()