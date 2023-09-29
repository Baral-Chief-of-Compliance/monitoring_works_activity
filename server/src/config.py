from dotenv import load_dotenv
import os


load_dotenv()

class Config(object):
    REDIS_HOST = os.getenv("REDIS_HOST")
    REDIS_PORT = os.getenv("REDIS_PORT")
    REDIS_DB = os.getenv("REDIS_DB")
    REDIS_SCREENSHOT_DB = os.getenv("REDIS_SCREENSHOT_DB")