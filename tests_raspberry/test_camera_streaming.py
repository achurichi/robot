from robot import camera_streaming
from threading import Thread


class Straming_daemon(Thread):

    def __init__(self, gamepad=None):
        self.gamepad = gamepad
        Thread.__init__(self)
        self.daemon = True
        self.start()

    def run(self):
        my_stream.start_streaming()


my_stream = camera_streaming.Stream()
daemon = Straming_daemon(my_stream)

while True:
    if my_stream.frame_processor.face_detection_on:
        input("Press Enter to disable face detection")
        my_stream.frame_processor.face_detection_on = False
    else:
        input("Press Enter to enable face detection")
        my_stream.frame_processor.face_detection_on = True
