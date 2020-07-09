import pygame, time
import RPi.GPIO as GPIO     # Importing RPi library to use the GPIO pins

servo_pin = 18     # Initializing the GPIO 21 for servo motor
GPIO.setmode(GPIO.BCM)          # We are using the BCM pin numbering
GPIO.setup(servo_pin, GPIO.OUT)     # Declaring GPIO 21 as output pin
p = GPIO.PWM(servo_pin, 50)     # Created PWM channel at 50Hz frequency
p.start(2.5)               

pygame.display.init()
pygame.joystick.init()
pygame.joystick.Joystick(0).init()

# Prints the joystick's name
JoyName = pygame.joystick.Joystick(0).get_name()
print("Name of the joystick:")
print(JoyName)
# Gets the number of axes
JoyAx = pygame.joystick.Joystick(0).get_numaxes()
print("Number of axis:")
print(JoyAx)

# Prints the values for axis0
while True:
    pygame.event.pump()
    axis_value = 10*(pygame.joystick.Joystick(0).get_axis(0)/2 + 0.5) + 2.5 
    print(axis_value)
    p.ChangeDutyCycle(axis_value) # Move servo to 180 degrees
    #time.sleep(0.2)
    
