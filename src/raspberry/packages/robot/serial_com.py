import glob
import serial
import crc16
import time
from threading import Thread
import json


class Serial_com:

    def get_crc(self, txt): return str(crc16.crc16xmodem(str.encode(txt)))

    def __init__(self, port=None, baud_rate=115200, timeout=0.25):  # timeout=0.025
        """Establish connection with the serial port. By default it 
        connects to the first available serial port
        """
        if port == None:
            ports = glob.glob('/dev/ttyUSB*')
        else:
            ports = glob.glob('/dev/' + port)
        self.serial_port = serial.Serial(ports[0], baud_rate, timeout=timeout)
        self.serial_port.flushInput()

        time.sleep(2)

    def write(self, data):
        """Write data to the serial port"""
        data_crc = data + '_' + self.get_crc(data) + '\n'
        self.serial_port.write(str.encode(data_crc))

    def read(self):
        """Read data from the serial port"""
        rawString = self.serial_port.readline().decode('utf-8').rstrip()
        idx = rawString.rfind('_')
        msg = rawString[:idx]
        crc = rawString[idx+1:]

        if self.get_crc(msg) == crc:
            return msg
        else:
            return '%%error'


class Serial_send_daemon(Thread):
    """Send a message through serial every x seconds.
    Defualt is 2ms."""

    def __init__(self, pi_serial, msg=None, interval=0.02):
        self.pi_serial = pi_serial
        self.msg = msg
        self.interval = interval
        Thread.__init__(self)
        self.daemon = True
        self.start()

    def run(self):
        while True:
            self.pi_serial.write(json.dumps(self.msg, separators=(',', ':')))
            time.sleep(self.interval)


class Serial_read_daemon(Thread):
    """Read the message comming from serial every x seconds.
    Defualt is 1s."""

    def __init__(self, pi_serial, interval=1):
        self.pi_serial = pi_serial
        self.interval = interval
        self.msg = None
        Thread.__init__(self)
        self.daemon = True
        self.start()

    def run(self):
        while True:
            self.msg = self.pi_serial.read()
            time.sleep(self.interval)
