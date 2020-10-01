from socket import *
import time
from threading import Thread, Lock

def receiver(clientSocket):
    while flag:
        '''Receive data from server using recvfrom'''
        print "\t\t"+recv_msg

flag = True

clientSocket = socket(AF_INET, SOCK_DGRAM)
addr = ('127.0.0.1', 12000)
name = str(raw_input("Enter Your Name:"))

clientSocket.sendto(name, addr)
#try:
    
# Start channel receiver thread
recv_thread = Thread(target=receiver, args=(clientSocket,))
recv_thread.daemon = True
recv_thread.start()

recv_msg = 'NUll'

while recv_msg != '*quit*':
    send_msg = raw_input()
    if send_msg == '*quit*':
        '''Send data to client using sendto'''
        flag = False
        recv_thread.stop()
    else:
        '''Send data to client using sendto'''