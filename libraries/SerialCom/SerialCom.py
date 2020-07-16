import glob
import serial
import zlib


class SerialCom:

    def get_crc(self, txt): return str(zlib.crc32(str.encode(txt)))

    def __init__(self, port=None, baud_rate=115200, timeout=0.25):  # timeout=0.025
        """Establish connection with the serial port. By default it 
        connects to the first available serial port
        """
        if port == None:
            ports = glob.glob('/dev/ttyUSB*')
        else:
            ports = glob.glob('/dev/' + port)
        self.serial_port = serial.Serial(ports[0], baud_rate, timeout=timeout)

    def write(self, data):
        """Write data to the serial port"""
        # data_crc = data + '_' + self.get_crc(data) + '\n'
        # self.serial_port.write(str.encode(data_crc))
        self.serial_port.write(str.encode(data + '\n'))

    def read(self):
        """Read data from the serial port"""
        rawString = self.serial_port.readline().decode('utf-8').rstrip()
        idx = rawString.find('_')
        msg = rawString[:idx]
        crc = rawString[idx+1:]

        if self.get_crc(msg) == crc:
            return msg
        else:
            return '%%error'
