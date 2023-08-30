import socket
import os

# Configuración del cliente
HOST = '127.0.0.1'
PORT = 12345

image_path = '../Images/imagen.png'  # Ruta de la imagen que deseas enviar

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))

# Obtener el tamaño de la imagen
image_size = os.path.getsize(image_path)
size_data = image_size.to_bytes(8, byteorder='big')
client_socket.sendall(size_data)

# Enviar la imagen
with open(image_path, 'rb') as f:
    while True:
        data = f.read(1024)
        if not data:
            break
        client_socket.sendall(data)

print("Imagen enviada.")

client_socket.close()


