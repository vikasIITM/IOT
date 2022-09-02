import socket
import time
import random

port=12346
s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(('',port))

client_ip_addr ='192.168.43.127'                                      

while True:   
  for i in range(0,3):
    local_var=str(random.randint(1,10))
    print("Sending random variable",local_var)
    s.sendto(local_var.encode('utf-8'),(client_ip_addr, port))
    time.sleep(1)  
  
  break
s.close()

