import glob
import serial
import time


# time.sleep(0.1)


class SerialCom:

    def __init__(self, port=None, baud_rate=115200):
        """Establish connection with the serial port. By default it 
        connects to the first available serial port
        """
        if port == None:
            ports = glob.glob('/dev/ttyUSB*')
        else:
            ports = glob.glob('/dev/' + port)
        self.serial_port = serial.Serial(ports[0], baud_rate)
        # time.sleep(2)

    def serial_write(self, data):
        """Write data to the serial port"""
        # try:
        self.serial_port.write(str.encode(data))
        # except serial.serialutil.SerialException:
        # pass

    def serial_read(self):
        """Read data from the serial port"""
        self.serial_port.write(str.encode(f'{axis_value:.2f}'))
        self.serial_port.close()
