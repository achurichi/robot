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

result = my_gamepad.gamepad_init()
try_count = 0

while result == False and try_count < 3:
    try_count += 1
    result = my_gamepad.gamepad_init()

if try_count < 3:
    update_data_daemon = update_data(my_gamepad)

    while True:
        pressed = my_gamepad.get_pressed()
        print(pressed)
        time.sleep(0.01)
else:
    print("Can't connect the gamepad")
