import cv2
import socketserver
from http import server


class Streaming_handler(server.BaseHTTPRequestHandler):

    def do_GET(self):
        if self.path == '/index.html':
            self.send_response(200)
            self.send_header('Age', 0)
            self.send_header('Cache-Control', 'no-cache, private')
            self.send_header('Pragma', 'no-cache')
            self.send_header(
                'Content-Type', 'multipart/x-mixed-replace; boundary=FRAME')
            self.end_headers()
            try:
                while True:
                    buffer = self.server.frame_processor.get_frame()
                    self.wfile.write(b'--FRAME\r\n')
                    self.send_header('Content-Type', 'image/jpg')
                    self.send_header('Content-Length', len(buffer))
                    self.end_headers()
                    self.wfile.write(buffer)
                    self.wfile.write(b'\r\n')
            except:
                pass
        else:
            self.send_error(404)
            self.end_headers()

    def log_message(self, format, *args):
        return


class Streaming_server(socketserver.ThreadingMixIn, server.HTTPServer):

    def __init__(self, frame_processor, server_address, RequestHandlerClass, bind_and_activate=True):
        self.frame_processor = frame_processor
        server.HTTPServer.__init__(
            self, server_address, RequestHandlerClass, bind_and_activate)

    allow_reuse_address = True
    daemon_threads = True


class Frame_processing():

    def __init__(self, camera, face_cascade_path, face_detection_on=False):
        self.camera = camera
        self.face_detection_on = face_detection_on
        self.face_cascade = cv2.CascadeClassifier(face_cascade_path)

    def get_frame(self):
        """Get a frame frome from the camera and encode it to jpeg"""
        grabbed, frame = self.camera.read()  # 640x480
        frame = frame[60:420, :]  # 640x360
        frame = cv2.rotate(frame, cv2.ROTATE_180)
        if self.face_detection_on:
            frame = self.face_detection(frame)
        encoded, buffer = cv2.imencode('.jpeg', frame)
        return buffer

    def face_detection(self, frame):
        """Detect faces and draw a square around them"""
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        faces = self.face_cascade.detectMultiScale(
            gray,
            scaleFactor=1.1,
            minNeighbors=5,
            minSize=(30, 30),
            flags=cv2.CASCADE_SCALE_IMAGE
        )
        for (x, y, w, h) in faces:
            cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
        return frame


class Stream():

    def __init__(self,
                 address=8000,
                 face_cascade_path='/home/pi/Documents/robot/src/raspberry/robot/haarcascade_frontalface_default.xml',
                 face_detection_on=False):
        """Initialize the camera to get the frames and the frame processor"""
        self.address = address
        self.camera = cv2.VideoCapture(0)
        self.frame_processor = Frame_processing(camera=self.camera,
                                                face_cascade_path=face_cascade_path,
                                                face_detection_on=face_detection_on)

    def start_streaming(self):
        """Start the streaming in a loop"""
        try:
            server = Streaming_server(frame_processor=self.frame_processor,
                                      server_address=('', self.address),
                                      RequestHandlerClass=Streaming_handler)
            server.serve_forever()
        finally:
            self.camera.release()
