from robot.serial_com import Serial_com
from robot.gamepad import Gamepad
from threading import Thread
import json
import time

pi_serial = Serial_com()

data = {"motor": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]}


class Send_data(Thread):
    """Send data to Arduino every 2ms"""

    def __init__(self, interval=0.02):
        self.interval = interval
        Thread.__init__(self)
        self.daemon = True
        self.start()

    def run(self):
        while True:
            pi_serial.write(json.dumps(data))
            time.sleep(self.interval)


class Update_gamepad(Thread):
    """Always reading the gamepad"""

    def __init__(self, gamepad=None):
        self.gamepad = gamepad
        Thread.__init__(self)
        self.daemon = True
        self.start()

    def run(self):
        self.gamepad.update()


my_gamepad = Gamepad()
gamepad_daemon = Update_gamepad(my_gamepad)

send_data_daemon = Send_data()

while True:
    pressed = my_gamepad.get_pressed()
    if 'right_horz_axis' in pressed:
        if pressed['right_horz_axis'] > 128 and data['motor'][0] < 128:
            data['motor'][0] += 1
        elif data['motor'][0] > 0:
            data['motor'][0] -= 1
        time.sleep(0.05)
