import random
from socket import *
from threading import Thread, Lock

client_info = {}

def receiver(serverSocket):
    global client_info
    global recv_msg
    global name
    while flag:
        #print "started"
        recv_msg, address = serverSocket.recvfrom(1024)
        #print bool(client_info)
        if bool(client_info):
            if address in client_info.keys():
                msg = "\t\t"+client_info[address]+":"+recv_msg
                print msg
                for addr in client_info:
                    '''Send data using sendto to addr'''    
            else:
                client_info[address] = recv_msg
                msg = "\n"+str(client_info[address])+" is online"
                print msg
                for addr in client_info:
                    '''Send data using sendto to addr'''    
        else:
            client_info[address] = recv_msg
            msg = "\n"+str(client_info[address])+" is online"
            print msg
            for addr in client_info:
                '''Send data using sendto to addr'''    
        
        



flag = True
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('', 12000))


#recv_msg, address = serverSocket.recvfrom(1024)
#client_addr = str(address[0])
#print recv_msg + "is connected from IP:"+str(address[0])+" and Port:"+str(address[1])+"\n"
#name = recv_msg

# Start channel receiver thread
'''Create a thread and call listener'''
recv_thread.daemon = True
recv_thread.start()
print "Server Started Listening.."

while flag:
    send_msg = raw_input()
    
    if send_msg == '*quit*':
        flag = False
        serverSocket.sendto(send_msg, address)
    else:
        serverSocket.sendto(send_msg, address)