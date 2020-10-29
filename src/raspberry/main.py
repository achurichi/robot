from robot.serial_com import *
from robot.gamepad import Gamepad, Gamepad_update_daemon
import time

data = {'motor': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        'state': 'test'}

pi_serial = Serial_com(baud_rate=115200)
send_daemon = Serial_send_daemon(pi_serial, data)
read_daemon = Serial_read_daemon(pi_serial)

my_gamepad = Gamepad()
print("Connecting...")
result = my_gamepad.connect(tries=3)

if result == True:
    print("Gamepad connected")
    gamepad_daemon = Gamepad_update_daemon(my_gamepad)

    while True:
        pressed = my_gamepad.get_pressed()
        if 'right_horz_axis' in pressed:
            if pressed['right_horz_axis'] > 128 and data['motor'][0] < 128:
                for i in range(6):
                    data['motor'][i] += 1
            elif data['motor'][0] > 0:
                for i in range(6):
                    data['motor'][i] -= 1
            time.sleep(0.003)
        if 'right_vert_axis' in pressed:
            if pressed['right_vert_axis'] > 128 and data['motor'][6] < 128:
                for i in range(6, 12):
                    data['motor'][i] += 1
            elif data['motor'][6] > 0:
                for i in range(6, 12):
                    data['motor'][i] -= 1
            time.sleep(0.003)
else:
    print("Can't connect the gamepad")
