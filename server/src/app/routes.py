from app import app, request, jsonify, redis_db, redis_screenshot
import json


@app.route('/', methods=["GET",])
def index():
    return jsonify("hello world")


@app.route('/all_conections', methods=["GET"])
def get_all_conections():
    if request.method == 'GET':
        keys = redis_db.keys()

        list_connections = []
        for k in keys:
            inf_connections = {}
            key_conect = k.decode('utf-8')

            for key, value in redis_db.hgetall(key_conect).items():
                inf_connections[key.decode("utf-8")] = value.decode("utf-8")

            key_conect = key_conect.split(":")
            inf_connections["ip"] = key_conect[0]
            inf_connections["port"] = key_conect[1]
            inf_connections["path"] = inf_connections["ip"].replace(".","_") + "_" + inf_connections["port"]
            
            list_connections.append(inf_connections)

            

        return jsonify({
                "connections": list_connections
        })


@app.route('/all_conections/<string:id_port>', methods=["GET"])
def get_inf_about_connection(id_port):
    if request.method == 'GET':
        id_port = id_port.split("_")
        
        inf_connections = {}
        key_connect = f'{id_port[0]}.{id_port[1]}.{id_port[2]}.{id_port[3]}:{id_port[4]}'

        for key, value in redis_db.hgetall(key_connect).items():
            inf_connections[key.decode("utf-8")] = value.decode("utf-8")

        inf_connections["ip"] = f'{id_port[0]}.{id_port[1]}.{id_port[2]}.{id_port[3]}'
        inf_connections["port"] = f'{id_port[4]}'

        return jsonify(inf_connections)
    

@app.route('/all_connections/<string:id_port>/get_screenshot', methods=['GET'])
def get_screenshot(id_port):
    id_port = id_port.split("_")
    key_connect = f'{id_port[0]}.{id_port[1]}.{id_port[2]}.{id_port[3]}:{id_port[4]}'

    redis_screenshot.set(key_connect, "photo")

    return jsonify("message_send")

