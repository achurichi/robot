import time
import pygame

pygame.display.init()
pygame.joystick.init()

control = pygame.joystick.Joystick(0)
control.init()

while True:
    pygame.event.pump()
    for i in range(17):
        axis_value = control.get_button(i) #control.get_axis(0-5)
        if axis_value == 1:
            print(f'Botón: {i}')
    time.sleep(0.2)