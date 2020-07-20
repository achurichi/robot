from robot.serial_com import Serial_com
import threading
import json

pi_serial = Serial_com()

data_set = {"pi_says": "Hello!", "numbers": [1.1, 2.123, 3]}


def send_data():
    pi_serial.write(json.dumps(data_set))
    threading.Timer(1, send_data).start()


def read_data():
    # test = json.loads(pi_serial.read())
    # print(test["m_1"])
    # print(test["m_2"])
    # print(test["m_3"])
    # print(test["state"])
    print(pi_serial.read())
    threading.Timer(1, read_data).start()


send_data()
read_data()
