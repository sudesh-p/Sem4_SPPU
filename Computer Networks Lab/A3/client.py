#!/usr/bin/env python 

""" 
A simple peer to peer chat
lines: 14
""" 

import socket 
from threading import Thread, Lock
import sys

def receiver(sock):
    while flag:
        '''Receive data from server''' #Receive data from server
        if data == 'quit':
            sys.exit(0)
        print ("\t\t"+data)

host = 'localhost'      #Server IP addres
port = 50000            #Port address 
size = 1024             #Size of packet data to receive
flag = True

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)    #Creating a Socket
sock.connect((host,port))   #Connect to Server

# Start Receiver Thread
hop = Thread(target=receiver, args=(sock,))
hop.daemon = True
hop.start() 

data = "random" #Entering any value so it is not quit initially     

while data != 'quit':   #User will enter 'quit' to exit server
    data = input()  #Enter message to send to server
    '''Send data to server'''   #Sending data to server
sock.close()    #Closing the socket