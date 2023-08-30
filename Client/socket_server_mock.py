import socket
import os

# Configuración del servidor
HOST = '127.0.0.1'
PORT = 12345

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen()

print("Esperando conexión...")

client_socket, client_address = server_socket.accept()
print("Conexión establecida desde:", client_address)

# Recibir tamaño de la imagen
size_data = client_socket.recv(8)
image_size = int.from_bytes(size_data, byteorder='big')

# Recibir la imagen
received_data = b''
while len(received_data) < image_size:
    data = client_socket.recv(1024)
    if not data:
        break
    received_data += data

# Guardar la imagen recibida
with open("received_image.png", "wb") as f:
    f.write(received_data)

print("Imagen recibida y guardada.")

client_socket.close()
server_socket.close()