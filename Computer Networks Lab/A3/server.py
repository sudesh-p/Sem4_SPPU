#!/usr/bin/env python 

""" 
A simple echo server 
""" 

import socket 
from threading import Thread, Lock
import sys

def receiver(sock):
    global flag
    while flag:
        '''Receive data from client''' #Receive client data
        if data == 'quit':
            sys.exit(0)
        print("\t\t"+data   )
    flag = True
    print ("Thread Exiting")

host = ''       #Server IP addres
port = 50000    #Port address 
backlog = 5     #For binding connections
size = 1024     #Size of packet data to receive
flag = True

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #Creating a Socket
s.bind((host,port))     #Binding Port and IP address
s.listen(backlog)       #Listen to connection

while 1: 
    print("Waiting for Peer to Join...")
    address =   #Accept a client connecion
    print ("Client "+str(address)+"joined chat.\n")
    
    # Start channel receiver thread
    '''Create a thread'''
    recv_thread.daemon = True
    recv_thread.start() 
    
    data = "random" #Entering any value so it is not quit initially     
    while data != 'quit':   #User will enter 'quit' to exit server
        data = input()  #Enter message to send to client
        '''Send data to client'''   #Sending data to client
    flag = False
    client.close()  #Closing the socket