from evdev import InputDevice, categorize, ecodes
import os


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

    def gamepad_init(self, event_num=1):
        """Initialize the connection with the gamepad. The default 
        event number is 1. Returns True if the connection was succesfully 
        stablished, otherwise returns False.
        """
        try:
            os.system(
                'expect /home/pi/Documents/robot/src/raspberry/packages/robot/bluetoothpair.sh')
            self.gamepad = InputDevice('/dev/input/event' + str(event_num))
        except:
            return False
        return True

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
