#!/usr/bin/env python3

from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='my_py_pkg',
            namespace='number_publisher',
            executable='number_publisher',
            name='number_publisher',
            output='screen',
            remappings=[('number', 'my_number')],
            parameters=[{'test_parameter': 2}]
        ),
    ])