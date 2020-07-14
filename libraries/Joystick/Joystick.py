import pygame


class Joystick:

    def __init__(self, id=0):
        self.joystick_init(id)

    def joystick_init(self, id=0):
        """Initialize the connection with the joystick.

        Parameters:
        id: Joystick id, default is 0.

        Returns True if the connection was succesfully stablished,
        otherwise returns False.
        """
        try:
            self.pygame = pygame
            self.pygame.display.init()
            self.pygame.joystick.init()

            self.control = pygame.joystick.Joystick(id)
            self.control.init()
        except:
            return False
        return True

    def get_button(self):
        """Returns a tuple with the pressed buttons, if no
        button has been pressed the tuple will be empty. 

        PS3 Dualshock outputs:
        0 -> X          9  -> START
        1 -> O          10 -> MENU
        2 -> Δ          11 -> L3
        3 -> □          12 -> R3
        4 -> L1         13 -> UP
        5 -> R1         14 -> DOWN
        6 -> L2         15 -> LEFT
        7 -> R2         16 -> RIGHT
        8 -> SELECT      
        """
        self.pygame.event.pump()
        pressed_buttons = []
        for i in range(17):
            if self.control.get_button(i) == 1:
                pressed_buttons.append(i)
        return tuple(pressed_buttons)

    def get_axes(self):
        """Returns a tuple with tuples of each axis and its postition. 

        PS3 Dualshock outputs:
        0 -> L3 horizontal 
        1 -> L3 vertical           
        2 -> L2           
        3 -> R3 horizontal  
        4 -> R3 vertical           
        5 -> R2          
        """
        self.pygame.event.pump()
        axes_values = []
        for i in range(6):
            axes_values.append((i, self.control.get_axis(i)))
        return tuple(axes_values)
