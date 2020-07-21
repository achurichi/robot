import cv2
import logging
import socketserver
from http import server


def frame_processing(camera):
    grabbed, frame = camera.read()  # grab the current frame
    frame = cv2.resize(frame, (640, 360))  # resize the frame
    # frame = cv2.transpose(frame)
    # frame = cv2.flip(frame, flipCode=0)
    encoded, buffer = cv2.imencode('.jpg', frame)
    return buffer


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
