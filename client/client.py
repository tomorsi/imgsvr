#!/usr/bin/python

import socket
 
UDP_IP2 = "192.168.16.19"
UDP_IP = "127.0.0.1"
UDP_PORT = 2048
MESSAGE = "abc"
 
print "UDP target IP:", UDP_IP
print "UDP target port:", UDP_PORT
print "message:", MESSAGE
 

for x in range(0,15):
    print "iteration: ", x
    sock = socket.socket(socket.AF_INET, # Internet
                         socket.SOCK_DGRAM) # UDP
    sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
