import random
from socket import *
from threading import Thread, Lock


def receiver(serverSocket):
    global recv_msg
    global name
    while flag:
        '''Receive data from using recvfrom'''
        if client_addr == str(address[0]):  
            if recv_msg == '*quit*':
                print name+" is offline"
            else:
                print "\t\t"+recv_msg



flag = True
'''Declare a socket for UDP'''
serverSocket.bind(('', 12000))

recv_msg, address = serverSocket.recvfrom(1024)
client_addr = str(address[0])
print recv_msg + " is connected from IP:"+str(address[0])+" and Port:"+str(address[1])+"\n"
name = recv_msg

# Start channel receiver thread
recv_thread = Thread(target=receiver, args=(serverSocket,))
recv_thread.daemon = True
recv_thread.start()


while flag:
    send_msg = raw_input()
    
    if send_msg == '*quit*':
        flag = False
        '''Send data to client using sendto'''
    else:
        '''Send data to client using sendto'''