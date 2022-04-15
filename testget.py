import sys
import zmq

context = zmq.Context()
socket = context.socket(zmq.SUB)
socket.connect("tcp://localhost:5556")
socket.setsockopt(zmq.SUBSCRIBE, b"")

while True:
    string  = socket.recv()
    print(string)