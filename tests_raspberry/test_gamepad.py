from evdev import InputDevice, categorize, ecodes

# creates object 'gamepad' to store the data
gamepad = InputDevice('/dev/input/event1')

# button code variables (change to suit your device)
left_horz_stick = 0
left_vert_stick = 1
right_horz_stick = 2
right_vert_stick = 5
horz_arrow = 16
left_value = -1
right_value = 1
vert_arrow = 17
up_value = -1
down_value = 1
aBtn = 304
bBtn = 305
xBtn = 307
yBtn = 308
L1 = 310
R1 = 311
L2 = 312
R2 = 313
select = 314
start = 315
L3 = 317
R3 = 318


# loop and filter by event code and print the mapped label
for event in gamepad.read_loop():
    if event.type == ecodes.EV_KEY or event.type == ecodes.EV_ABS:
        if event.code == left_horz_stick:
            print("left_horz_stick"),
        elif event.code == left_vert_stick:
            print("left_vert_stick"),
        elif event.code == right_horz_stick:
            print("right_horz_stick"),
        elif event.code == right_vert_stick:
            print("right_vert_stick"),
        elif event.code == horz_arrow:
            print("horz_arrow"),
        elif event.code == vert_arrow:
            print("vert_arrow"),
        elif event.code == aBtn:
            print("A"),
        elif event.code == bBtn:
            print("B"),
        elif event.code == xBtn:
            print("X"),
        elif event.code == yBtn:
            print("Y"),
        elif event.code == L1:
            print("L1"),
        elif event.code == R1:
            print("R1"),
        elif event.code == L2:
            print("L2"),
        elif event.code == R2:
            print("R2"),
        elif event.code == L3:
            print("L3"),
        elif event.code == R3:
            print("R3"),
        elif event.code == select:
            print("select"),
        elif event.code == start:
            print("start"),

        print(event.value)

        # print(device.capabilities())
# device.capabilities(verbose=True))
