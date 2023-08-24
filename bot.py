import telebot
from telebot import types 
import socket


def map_range(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min


server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('192.168.88.245', 80))
server_socket.listen(1)

print("Сервер запущен")
tempBase = 0
tempStreet = 0

token = "6401093173:AAG4tXyo1yn_lDYeh-1G0WUKcWq02oD6NUE"
bot = telebot.TeleBot(token)
keyboard = types.ReplyKeyboardMarkup(row_width=1, resize_keyboard=False, one_time_keyboard=True)
btn1 = types.KeyboardButton(text = "❓ узнать")
keyboard.add(btn1)
while True: 
    client_socket, client_address = server_socket.accept()
    print(f"Подключение установлено с {client_address}")

    data = str(client_socket.recv(1024))
    data = data.replace("b", "")
    data = data.replace("'", "")
    data = data.replace("\\r\\n", "")
    print(f"Получены данные: {data}")
    mas = data.split(";")
    temp = float(mas[1])
    
    if(mas[0] == '1'):
        tempStreet = temp

    if(mas[0] == '2'):
        tempBase = temp
        packet = ""

        if(tempBase < 26 and tempBase > 24):
            packet = "0;0"
        else:
            if (tempBase < tempStreet and tempStreet - tempBase > 1) :
                packet = packet + '1'
            else: 
                packet = packet + '0'

            packet = packet + ';'

            if(tempBase > tempStreet and tempBase - tempStreet > 1):

                packet = packet + str(int(map_range(tempBase-tempStreet, 0, 30, 200, 255)))

            else: packet = packet + "0"

        client_socket.sendall(packet.encode())
        print(f"Отправлены данные: {packet}")
        @bot.message_handler(commands=['start'])
        def start_message(message):
            bot.send_message(message.chat.id, "Hello World!", reply_markup=keyboard)
        @bot.message_handler(content_types=['text'])
        def func(message):
            if(message.text == "❓ узнать"):
                        if packet[0] == '1':
                            x = "открыто"
                        else:
                            x = "закрыто"
                        bot.send_message(message.chat.id, text=f"температура на улице: {tempStreet}, температура в здание: {tempBase}, окно: {x}, скорость вентилятора {str(int(map_range(tempBase-tempStreet, 0, 30, 200, 255)))}")

        bot.polling(none_stop=True)