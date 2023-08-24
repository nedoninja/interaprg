import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('192.168.88.245', 80))
server_socket.listen(1)

print("Сервер запущен и ожидает подключений...")
client_socket, client_address = server_socket.accept()
print(f"Подключение установлено с {client_address}")

while True:
    data = client_socket.recv(1024)
    print(f"Получены данные: {data}")

# client_socket.close()
# server_socket.close()
