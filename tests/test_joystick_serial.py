import time, pygame, glob, serial

pygame.display.init()
pygame.joystick.init()
control = pygame.joystick.Joystick(0)
control.init()

ports = glob.glob('/dev/ttyUSB*')
arduino = serial.Serial(ports[0], 57600)

time.sleep(2)
while True:
    pygame.event.pump()
    axis_value = 180*(pygame.joystick.Joystick(0).get_axis(0)/2 + 0.5) 
    print(f'{axis_value:.1f}')
    try:
        arduino.write(str.encode(f'{axis_value:.2f}'))
    except serial.serialutil.SerialException:
        pass
    time.sleep(0.1)
arduino.close()