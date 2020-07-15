from SerialCom import SerialCom
import time
import threading

pi_serial = SerialCom()


def send_data():
    pi_serial.write("Raspberry says Hello!")
    # pi_serial.read()
    threading.Timer(0.9, send_data).start()


def read_data():
    print(pi_serial.read())
    threading.Timer(1, read_data).start()


send_data()
read_data()
