 

import socket
import time
from datetime import datetime

# Get the local host name
myHostName = socket.gethostname()
print("Name of the localhost is {}".format(myHostName))

# Get the IP address of the local host
myIP = socket.gethostbyname(myHostName)
print("IP address of the localhost is {}".format(myIP))

# # While Run on Laptop gives
# Name of the localhost 
# IP address of the localhost 

port=12346

s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind((myIP, port))
starttime=datetime.now()
print("Client is ready .....")
while True:
  data,addr=s.recvfrom(1024)
  print('Received:',data.decode('utf-8'),'from',addr)
  
  time=datetime.now()-starttime
  if time.total_seconds()>=50:
      
  
      break
s.close()


