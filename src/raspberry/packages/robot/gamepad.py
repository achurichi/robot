from evdev import InputDevice, categorize, ecodes
import subprocess
import os
from threading import Thread
import time


BLUETOOTH_FILE = os.path.join(os.path.dirname(
    __file__), 'bluetoothpair.sh')


class Gamepad:

    def __init__(self):
        self.codes = {
            0: 'left_horz_axis',
            1: 'left_vert_axis',
            2: 'right_horz_axis',
            5: 'right_vert_axis',
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

        self.btn_values = {
            'left_horz_axis': 128,
            'left_vert_axis': 128,
            'right_horz_axis': 128,
            'right_vert_axis': 128,
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

    def connect(self, event_num=1, tries=1):
        """Initialize the connection with the gamepad. The default 
        event number is 1. The default number of tries is 1.
        Returns True if the connection was successfully stablished, 
        otherwise returns False.
        """
        tries_count = 0

        while tries_count < tries:
            tries_count += 1
            try:
                subprocess.run(['expect', BLUETOOTH_FILE],
                               stdout=subprocess.DEVNULL,
                               timeout=30)
                self.gamepad = InputDevice('/dev/input/event' + str(event_num))
                return True
            except:
                pass

        return False

    def get_pressed(self):
        """Returns a dict with the pressed buttons or moved axis controlles"""

        pressed = {k: v for k, v in self.btn_values.items() if v != 0}
        pressed['left_horz_axis'] = self.btn_values['left_horz_axis']
        pressed['left_vert_axis'] = self.btn_values['left_vert_axis']
        pressed['right_horz_axis'] = self.btn_values['right_horz_axis']
        pressed['right_vert_axis'] = self.btn_values['right_vert_axis']

        if pressed['left_horz_axis'] == 128:
            del pressed['left_horz_axis']
        if pressed['left_vert_axis'] == 128:
            del pressed['left_vert_axis']
        if pressed['right_horz_axis'] == 128:
            del pressed['right_horz_axis']
        if pressed['right_vert_axis'] == 128:
            del pressed['right_vert_axis']

        return pressed

    def update(self):
        """Runs forever and update the value of buttons and axis when 
        they are pressed    
        """
        for event in self.gamepad.read_loop():
            if event.type == ecodes.EV_KEY or event.type == ecodes.EV_ABS:
                if event.code in self.codes.keys():
                    self.btn_values[self.codes[event.code]] = event.value


class Gamepad_update_daemon(Thread):

    def __init__(self, gamepad=None):
        self.gamepad = gamepad
        Thread.__init__(self)
        self.daemon = True
        self.start()

    def run(self):
        self.gamepad.update()
