import socket
import os
from time import sleep

def main():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('127.0.0.1', 1717))

    image_path = "Images/"  # Cambia esto al camino de tu imagen
    image_name = "imagen.png"
    image_path += image_name

    # # Enviar la longitud del archivo al servidor
    image_size = os.path.getsize(image_path)
    print(type(image_size))
    print(image_size)
    client_socket.sendall(f'cols\0'.encode())
    sleep(1)
    client_socket.sendall(f'/{image_name}\0'.encode())
    sleep(1)
    client_socket.sendall(f'{image_size}\0'.encode())
    sleep(1)
    # # Enviar la imagen al servidor en fragmentos
    with open(image_path, 'rb') as f:
        while True:
            data = f.read(4096)
            if not data:
                sleep(1)
                client_socket.sendall(f'exit\0'.encode())
                break
            client_socket.sendall(data)
            sleep(1)

    print("Imagen enviada al servidor.")

    # Recibiendo la longitud de la imagen del servidor
    image_size = int(client_socket.recv(1024).decode())

    received_data = b""
    # Recibiendo la imagen en fragmentos
    while len(received_data) < image_size:
        data = client_socket.recv(1024)
        received_data += data

    # Guardando la imagen recibida del servidor
    with open("Client/received_image_from_server.jpg", "wb") as file:
        file.write(received_data)

    print("Imagen recibida del servidor y guardada.")

    client_socket.close()

if __name__ == "__main__":
    main()
