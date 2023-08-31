import socket
import os

def socket_send_image(ip, port, image_name):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # client_socket.connect(('127.0.0.1', port))
    client_socket.connect((ip, port))

    image_path = "Python/Client/ClientImages/" 
    image_path += image_name

    # # Enviar la longitud del archivo al servidor
    # client_socket.sendall(f'/{image_name}\0'.encode())

    image_size = os.path.getsize(image_path)
    image_size = f'{image_size}\0'.encode()
    client_socket.sendall(image_size)
    # # Enviar la imagen al servidor en fragmentos
    with open(image_path, 'rb') as f:
        while True:
            data = f.read(4096)
            if not data:
                # client_socket.sendall(f'exit\0'.encode())
                break
            client_socket.sendall(data)

    print("Imagen enviada al servidor.")
    client_socket.close()
