from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([

        Node(
            package='joy',
            executable='game_controller_node',
            name='controller_1',
            parameters=[{'device_id': 0}],
            remappings=[('/joy', '/joy1')],
        ),
        
        Node(
            package="teleoperator",
            executable='controls',
            name='controls',
            output='screen'
        )
    ])