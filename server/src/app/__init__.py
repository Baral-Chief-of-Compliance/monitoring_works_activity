from flask import Flask, jsonify, request
from config import Config
import redis
from flask_cors import CORS


app = Flask(__name__)
app.config.from_object(Config)
CORS(app)


redis_db = redis.Redis(
    host=app.config['REDIS_HOST'], 
    port=app.config['REDIS_PORT'],
    db=app.config['REDIS_DB']
)

redis_screenshot = redis.Redis(
    host=app.config['REDIS_HOST'], 
    port=app.config['REDIS_PORT'],
    db=app.config['REDIS_SCREENSHOT_DB']
)

from app import routes