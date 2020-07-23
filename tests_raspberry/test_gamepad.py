from robot.gamepad import Gamepad
from threading import Thread
import time


class update_data(Thread):

    def __init__(self, gamepad=None):
        self.gamepad = gamepad
        Thread.__init__(self)
        self.daemon = True
        self.start()

    def run(self):
        self.gamepad.update()


my_gamepad = Gamepad()
update_data_daemon = update_data(my_gamepad)

while True:
    pressed = my_gamepad.get_pressed()
    print(pressed)
    time.sleep(0.01)
