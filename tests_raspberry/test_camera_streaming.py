from robot.camera_streaming import Stream, Stream_daemon

my_stream = Stream()
daemon = Stream_daemon(my_stream)

while True:
    if my_stream.frame_processor.face_detection_on:
        input("Press Enter to disable face detection")
        my_stream.frame_processor.face_detection_on = False
    else:
        input("Press Enter to enable face detection")
        my_stream.frame_processor.face_detection_on = True
