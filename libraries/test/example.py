import serial
import time
import threading


ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)

# while True:
#     ser.write(b"Raspberry says Hello!\n")
#     line = ser.readline()
#     time.sleep(0.02)


class send_data(object):

    def __init__(self, interval=1):
        self.interval = interval
        thread = threading.Thread(target=self.run, args=())
        thread.daemon = True
        thread.start()

    def run(self):
        while True:
            ser.write(b"Raspberry says Hello!\n")
            # line = ser.readline()
            time.sleep(self.interval)


send_data_daemon = send_data(0.02)
time.sleep(30)
