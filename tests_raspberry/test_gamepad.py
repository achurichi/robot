from evdev import InputDevice, categorize, ecodes
import os

# button code variables
codes = {
    0: 'left_horz_stick',
    1: 'left_vert_stick',
    2: 'right_horz_stick',
    5: 'right_vert_stick',
    16: 'horz_arrow',
    17: 'vert_arrow',
    304: 'A',
    305: 'B',
    307: 'X',
    308: 'Y',
    310: 'L1',
    311: 'R1',
    312: 'L2',
    313: 'R2',
    314: 'select',
    315: 'start',
    317: 'L3',
    318: 'R3',
}

btn_values = {
    'left_horz_stick': 128,
    'left_vert_stick': 128,
    'right_horz_stick': 128,
    'right_vert_stick': 128,
    'horz_arrow': 0,
    'vert_arrow': 0,
    'A': 0,
    'B': 0,
    'X': 0,
    'Y': 0,
    'L1': 0,
    'R1': 0,
    'L2': 0,
    'R2': 0,
    'select': 0,
    'start': 0,
    'L3': 0,
    'R3': 0,
}


def get_pressed(btn_values):
    pressed = {k: v for k, v in btn_values.items() if v != 0}
    pressed['left_horz_stick'] = btn_values['left_horz_stick']
    pressed['left_vert_stick'] = btn_values['left_vert_stick']
    pressed['right_horz_stick'] = btn_values['right_horz_stick']
    pressed['right_vert_stick'] = btn_values['right_vert_stick']

    if pressed['left_horz_stick'] == 128:
        del pressed['left_horz_stick']
    if pressed['left_vert_stick'] == 128:
        del pressed['left_vert_stick']
    if pressed['right_horz_stick'] == 128:
        del pressed['right_horz_stick']
    if pressed['right_vert_stick'] == 128:
        del pressed['right_vert_stick']

    return pressed


def gamepad_init():
    # print('pase')
    os.system('expect bluetoothpair.sh')


gamepad_init()

# creates object 'gamepad' to store the data
gamepad = InputDevice('/dev/input/event1')

# loop and filter by event code and print the mapped label
for event in gamepad.read_loop():
    if event.type == ecodes.EV_KEY or event.type == ecodes.EV_ABS:
        if event.code in codes.keys():
            btn_values[codes[event.code]] = event.value
            print(get_pressed(btn_values))
