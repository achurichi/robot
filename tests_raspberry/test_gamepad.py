from robot.gamepad import Gamepad, Gamepad_update_daemon
import time

my_gamepad = Gamepad()
print("Connecting...")
result = my_gamepad.connect(tries=3)

if result == True:
    print("Gamepad connected")
    daemon = Gamepad_update_daemon(my_gamepad)

    while True:
        pressed = my_gamepad.get_pressed()
        print(pressed)
        time.sleep(0.01)
else:
    print("Can't connect the gamepad")
