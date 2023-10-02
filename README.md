# monitoring_works_activity

## Принцип работы
Идея была сделать такое взаимодейтсвие. Клиент сокеты на плюсах подключатся к сокет-серверу на питоне.
Клиентские сокеты каждые 10 секунд отправляют данные логин, пользователя, домен. Сервер сокет на основании этих данных и данных о времени, адресе и порте создаёт словарь,
который помещается в редис. 
Далее чтобы просматривать все эти данные был создан API сервер на flask. И были прописаны эндпоинты на получение всех подключений и получение ифнормации о конкретном подключении.
Была также создана клиенсткая часть на vue3 которая с помощью axios подключается к серверной части на flask и отображает данные. Был использован такеж фреймворк элементов - vuetify.
На страницы конкретного подключения есть кнопка получить скриншот. При её нажатии отправляется Get запрос на серверную часть на flask, после этого заносится информацию в редис в другую бд для сообщений,
кдючом явялется ip:port на котором весит клиенсткий сокет. При получении сообщений от клиентов, сервер сокет проверяет вторую бд сообщений на наличие ip:port если есть, то шлет команду сдлеать скриншот.
На этом момент я и остновился. Не нашел как получившийся скриншот, его битмапу отправить через send на сервер сокет.

Для установки и просмотра всего этого чуда, необходимо, если вы на линуксе или wsl командой redis-server 6379.conf  запустить сервер редис
в папке /server/src создайте фаил .env и пропишите в нем следующее 

REDIS_HOST="localhost"
REDIS_PORT=6379
REDIS_DB=4
REDIS_SCREENSHOT_DB=5

после этого в корне проекта командой pip install -r requirements.txt установить все зависимости для серверной части
Для запуска серверной части py main.py в папке /server/src/

Сокет сервер в папке /socket_server py server.py


Клиентский сокет запускается в /client запуском client.exe

Или можно ещё раз скомпилировать client.cpp 
g++ client.cpp -o client -lws2_32 -lgdi32

в папке /server/frontend/frontend-vue прописать yarn чтобы установить все зависимости
и после этого yarn dev чтобы запусть клиентскую часть



 Скриншоты того, что вышло
запсук client.exe
![image](https://github.com/Baral-Chief-of-Compliance/monitoring_works_activity/assets/78692798/eaa1e523-0f08-4a62-ae7f-2f8a6d268b34)

вводим логин 
![image](https://github.com/Baral-Chief-of-Compliance/monitoring_works_activity/assets/78692798/39315069-bc85-4803-832e-b3abb2120646)

работает в фоне
![image](https://github.com/Baral-Chief-of-Compliance/monitoring_works_activity/assets/78692798/d98220b9-4687-4948-8bdb-ee4dd2f9c68c)


обработанные данные от сокет клиента
![image](https://github.com/Baral-Chief-of-Compliance/monitoring_works_activity/assets/78692798/e2ecec90-a1dd-4232-81a6-15e4c2fea7e5)


 ![image](https://github.com/Baral-Chief-of-Compliance/monitoring_works_activity/assets/78692798/c9030e0e-662a-42cc-b220-6f192720999f)


![image](https://github.com/Baral-Chief-of-Compliance/monitoring_works_activity/assets/78692798/8a7cd0b4-e898-4bdf-a121-56e04bba6e21)





 
