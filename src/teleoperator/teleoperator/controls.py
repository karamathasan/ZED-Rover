import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from std_msgs.msg import Float32MultiArray

import teleoperator.layout as layout

# converts Joy Node controls into meaningful motor inputs
def arcade_drive(throttle, steer):
    left_motor = throttle + steer
    right_motor = throttle - steer
    
    # Find the maximum absolute value
    max_val = max(abs(left_motor), abs(right_motor))
    
    # Normalize if exceeding motor limits
    if max_val > 1.0:
        left_motor /= max_val
        right_motor /= max_val
        
    return [left_motor, right_motor]


class Controls(Node):
    def __init__(self):
        super().__init__('controls')
        self.latest = [0.0,0.0]
        self.joy_sub = self.create_subscription(
            Joy,
            "/joy1",
            self.controller_callback,
            10
        )
        
        self.pub = self.create_publisher(
            Float32MultiArray,
            "/motor_input",
            10
        )
        
        self.delayed_publisher = self.create_timer(0.1, self.publish_latest)
        
        self.get_logger().info("Controls Ready")
        
    def controller_callback(self, msg: Joy):
        # throttle = msg.axes[layout.LEFTY]
        # steer = msg.axes[layout.LEFTX]
        
        # self.latest = arcade_drive(throttle,steer)
        left = msg.axes[layout.LEFTY]
        right = msg.axes[layout.RIGHTY]
        self.latest = [left,right]
        
        # ignore, apply tank drive for now
   
        # self.pub.publish(out)
        
        # msg.
        # axes = msg.axes
        # buttons = msg.buttons
        # self.get_logger().info(f"AXES:{axes}\nBUTTONS:{buttons}")
        
    def publish_latest(self):
        out = Float32MultiArray()
        out.data = self.latest
        self.pub.publish(out)
        
        
def main(args=None):
    rclpy.init(args=args)

    node = Controls()

    rclpy.spin(node)

    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()