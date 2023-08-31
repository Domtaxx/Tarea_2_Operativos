import socket
import os

def main():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('127.0.0.1', 8888))

    image_path = "Images/"  # Cambia esto al camino de tu imagen
    image_name = "imagen.png"
    image_path += image_name

    # # Enviar la longitud del archivo al servidor
    image_size = os.path.getsize(image_path)
    print(type(image_size))
    print(image_size)
    size_data = image_size.to_bytes(8, byteorder='big')
    client_socket.sendall(size_data)

    # # Enviar la imagen al servidor en fragmentos
    with open(image_path, 'rb') as f:
        while True:
            data = f.read(1024)
            if not data:
                break
            client_socket.sendall(data)

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
