#!/usr/bin/env python3

import rclpy
from rclpy.node import Node

from example_interfaces.srv import AddTwoInts
from functools import partial

class AddTwoIntsClientNode(Node):
    def __init__(self):
        super().__init__('add_two_ints_client')
        self.get_logger().info('Client has been started')
        self.call_add_two_ints(1, 12)
            
    def call_add_two_ints(self, a, b):
        client = self.create_client(AddTwoInts, 'add_two_ints')
        while not client.wait_for_service(timeout_sec=1.0):
            self.get_logger().warn('service not available, waiting again...')
            
        request = AddTwoInts.Request()
        request.a = a
        request.b = b
        future = client.call_async(request)    
        future.add_done_callback(partial(self.call_back, a=a, b=b))        
            
    def call_back(self, future, a, b):
        try:
            response = future.result()
            self.get_logger().info('%d + %d = %d' % (a, b, response.sum))
        except Exception as e:
            self.get_logger().error('Service call failed %r' % (e,))
            
def main(args=None):
    rclpy.init(args=args)
    node = AddTwoIntsClientNode()
    rclpy.spin(node)
    rclpy.shutdown()
    
if __name__ == '__main__':
    main()