from socket import *
import time
from threading import Thread, Lock

def receiver(clientSocket):
    global recv_msg
    while flag:
        '''receive data from server'''
        print "\t\t"+recv_msg

flag = True

clientSocket = socket(AF_INET, SOCK_DGRAM)
addr = ('127.0.0.1', 12000)
name = str(raw_input("Enter Your Name:"))

'''Send name to client'''
#try:
    
# Start channel receiver thread
recv_thread = Thread(target=receiver, args=(clientSocket,))
recv_thread.daemon = True
recv_thread.start()

recv_msg = 'NUll'

while recv_msg != '*quit*':
    send_msg = raw_input()
    if send_msg == '*quit*':
        '''Send the data'''
        flag = False
        recv_thread.stop()
    else:
        '''Send the data'''