import socket
import os
import time
import getpass
import platform
from datetime import datetime, date
import json

ClientSocket = socket.socket()
host = 'localhost'
port = 3000

login = input("enter your login: ")

print('Waiting for connection')
try:
    ClientSocket.connect((host, port))
except socket.error as e:
    print(str(e))

Response = ClientSocket.recv(1024)
print(Response.decode('utf-8'))
while True:
    # Input = input('Say Something: ')
    # ClientSocket.send(str.encode(Input))
    # Response = ClientSocket.recv(1024)
    # print(Response.decode('utf-8'))
    now = datetime.now()
    today = date.today()

    data = {
        "name": getpass.getuser(),
        "domain": os.environ['userdomain'],
        "time": now.strftime("%H:%M:%S"),
        "date": today.strftime("%d/%m/%Y"),
        "login": login
    }

    data_b = json.dumps(data)

    ClientSocket.send(bytes(data_b, encoding='utf-8'))
    Response = ClientSocket.recv(1024)

    if (Response.decode() == "make_a_photo"):
        ClientSocket.send(bytes("photo_is_made", encoding='utf-8'))

    print("response:", Response)

    

    # print(socket.gethostname())
    time.sleep(10)
    # ClientSocket.close()

