import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import serial
import json
import random


class ArduinoNode(Node):
    def __init__(self):
        super().__init__('arduino_node')
        self.publisher = self.create_publisher(String, 'pantemaskin/flasker', 10)
        self.get_logger().info('Pantemaskin node startet!')
        
        # Tell flasker
        self.accepted = 0
        self.rejected = 0

        # Simuler data hvis ingen Arduino
        self.timer = self.create_timer(2.0, self.simulate_data)

    def simulate_data(self):
        accepted = random.choice([True, True, True, False])
        if accepted:
            self.accepted += 1
        else:
            self.rejected += 1

        data = {
            'item_id': self.accepted + self.rejected,
            'accepted': accepted,
            'total_accepted': self.accepted,
            'total_rejected': self.rejected
        }

        msg = String()
        msg.data = json.dumps(data)
        self.publisher.publish(msg)
        self.get_logger().info(f'Flaske {"godkjent ✓" if accepted else "avvist ✗"} | Godkjent: {self.accepted} | Avvist: {self.rejected}')

def main(args=None):
    rclpy.init(args=args)
    node = ArduinoNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
