from robot.serial_com import Serial_com
import time
import threading

pi_serial = Serial_com()


def send_data():
    pi_serial.write("Raspberry says Hello!")
    threading.Timer(0.02, send_data).start()


def read_data():
    print(pi_serial.read())
    threading.Timer(1, read_data).start()


send_data()
read_data()
