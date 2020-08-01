from robot.serial_com import *
import time

pi_serial = Serial_com()

send_daemon = Serial_send_daemon(pi_serial, {'Raspberry': 'Hello!'})
read_daemon = Serial_read_daemon(pi_serial)

while True:
    print(read_daemon.msg)
    time.sleep(1)
