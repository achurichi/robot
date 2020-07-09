import cv2
import numpy as np


def empty(a):
    pass


camera = cv2.VideoCapture(0)

# cv2.namedWindow('Trackbars')
# cv2.resizeWindow('Trckbars', 640, 240)
# cv2.createTrackbar('Contrast', 'Trackbars', 110, 255, empty)

while True:
    # contrast = cv2.getTrackbarPos('Contrast', 'Trackbars')
    camera.set(10, 53)

    ret, frame = camera.read()
    cv2.imshow('Video', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

camera.release()
cv2.destroyAllWindows()
