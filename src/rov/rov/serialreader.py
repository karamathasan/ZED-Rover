import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray

import serial
import struct
import time
import threading

# read sensor or other values from pico

class SerialReader(Node):
    def __init__(self):
        super().__init__('serial_reader')
        self.port = '/dev/ttyACM0'   # CHANGE if needed
        self.baudrate = 115200

        try:
            self.ser = serial.Serial(self.port, self.baudrate, timeout=1)
            time.sleep(2)  # allow device reset
            self.get_logger().info(f"Serial connected on {self.port}")
        except Exception as e:
            self.get_logger().error(f"Serial connection failed: {e}")
            self.ser = None        
            
        # self.pub = self.create_publisher("")
        
    def reader_callback(self,msg:Float32MultiArray):
        data = msg.data


def main(args = None):
    rclpy.init(args = args)
    writer = SerialReader()
    rclpy.spin(writer)
    writer.destroy()
    rclpy.shutdown()
    
if __name__ == "__main__":
    main()