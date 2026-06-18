import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from std_msgs.msg import String
import json

# converts Joy Node controls into meaningful motor inputs
class Controls(Node):
    def __init__(self):
        super().__init__('controls')
        
        self.joy_sub = self.create_subscription(
            Joy,
            "/joy1",
            self.controller_callback,
            10
        )
        
        self.get_logger().info("Controls Ready")
        
    def controller_callback(self, msg: Joy):
        axes = msg.axes
        buttons = msg.buttons
        self.get_logger().info(f"AXES:{axes}\nBUTTONS:{buttons}")
        
        
def main(args=None):
    rclpy.init(args=args)

    node = Controls()

    rclpy.spin(node)

    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()