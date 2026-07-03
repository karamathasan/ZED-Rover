import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray

import serial
import struct
import time

# send motor input to raspberry pi pico

class SerialWriter(Node):
    def __init__(self):
        super().__init__('serial_writer')
        
        self.port = '/dev/ttyACM0'   # CHANGE if needed
        self.baudrate = 115200

        try:
            self.ser = serial.Serial(self.port, self.baudrate, timeout=1, write_timeout=0.5)
            time.sleep(2)  # allow device reset
            self.get_logger().info(f"Serial connected on {self.port}")
        except Exception as e:
            self.get_logger().error(f"Serial connection failed: {e}")
            self.ser = None
            self.destroy_node()
        
        self.controls_sub = self.create_subscription(
            Float32MultiArray,
            "/motor_input",
            self.writer_callback,
            10
        )
        
    def writer_callback(self,msg:Float32MultiArray):
        if self.ser:
            inputs = msg.data
            self.get_logger().info(f"sending:{inputs}")
            packet = struct.pack("<ff",*inputs)
            self.ser.write(packet)
        else:
            self.get_logger().info(f"serial not opened")
        
def main(args = None):
    rclpy.init(args = args)
    writer = SerialWriter()
    rclpy.spin(writer)
    writer.destroy_node()
    rclpy.shutdown()
    
if __name__ == "__main__":
    main()
        