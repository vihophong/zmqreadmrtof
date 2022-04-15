#!/home/daq/venv/bin/python

import time
import sys
import zmq
import random
def follow(thefile):
    #print all content
    flag_read = False
    while True:
        line1 = thefile.readline()
        if (not line1):
            break
        line1 = line1.strip()
        if (flag_read):
            # time.sleep(0.001)
            yield line1
        if (line1 == "[DATA]"):
            flag_read = True
    print("eof")
    thefile.seek(0,2)
    while True:
        line = thefile.readline()
        if not line:
            time.sleep(0.1)
            continue
        yield line

if __name__ == '__main__':
    logfile = open(sys.argv[1],"r")
    nsent = 0
    context = zmq.Context()
    socket = context.socket(zmq.PUSH)
    socket.bind("tcp://*:5556")
    # socket.setsockopt(zmq.SNDBUF, 8)
    loglines = follow(logfile)
    for line in loglines:
        socket.send(b"%s" % (line.strip().encode("utf-8")))
        nsent+=1
        # print(nsent)
        # print(line.strip())
