import Joystick
import time

myJoy = Joystick()
while True:
    btn = myJoy.get_button()
    if btn != ():
        print('Buttons', btn)
    print('Axes:', myJoy.get_axes())
    time.sleep(0.2)
