import cv2
import logging
import socketserver
from http import server
import time

faceCascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')


def frame_processing(camera):
    grabbed, frame = camera.read()  # 640x480
    frame = frame[60:420, :]  # 640x360
    frame = cv2.rotate(frame, cv2.ROTATE_180)

    frame = face_detection(frame)

    encoded, buffer = cv2.imencode('.jpg', frame)

    return buffer


def face_detection(frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.1,
        minNeighbors=5,
        minSize=(30, 30),
        flags=cv2.CASCADE_SCALE_IMAGE
    )
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)

    return frame


class streaming_handler(server.BaseHTTPRequestHandler):
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
                    buffer = frame_processing(camera)
                    self.wfile.write(b'--FRAME\r\n')
                    self.send_header('Content-Type', 'image/jpg')
                    self.send_header('Content-Length', len(buffer))
                    self.end_headers()
                    self.wfile.write(buffer)
                    self.wfile.write(b'\r\n')
            except Exception as e:
                logging.warning(
                    'Removed streaming client %s: %s',
                    self.client_address, str(e))
        else:
            self.send_error(404)
            self.end_headers()


class streaming_server(socketserver.ThreadingMixIn, server.HTTPServer):
    allow_reuse_address = True
    daemon_threads = True


camera = cv2.VideoCapture(0)

try:
    address = ('', 8000)
    server = streaming_server(address, streaming_handler)
    server.serve_forever()
finally:
    camera.release()
