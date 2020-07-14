from SerialCom import SerialCom
import time

pi_serial = SerialCom()

# pi_serial.write("Raspberry says Hello!")
# print("Raspberry says Hello!")

# while True:
# time.sleep(1)
# print(pi_serial.read())
# if pi_serial.read() == "Arduino says Hello!":
    # print("Raspberry received Hello from Arduino")
    # time.sleep(1)
    # pi_serial.write("Raspberry says Hello!")
    #     print("Raspberry says Hello!")
    #     time.sleep(1)
    # else:
    # pi_serial.write("Raspberry says Hello!")
    # print("Raspberry says Hello!")

pi_serial.write("Raspberry says Hello!")
