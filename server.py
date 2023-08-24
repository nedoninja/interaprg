import socket


def map_range(x, in_min, in_max, out_min, out_max):
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min


server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('192.168.88.245', 80))
server_socket.listen(1)

print("Сервер запущен")

tempBase = 0
tempStreet = 0

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

# client_socket.close()
# server_socket.close()