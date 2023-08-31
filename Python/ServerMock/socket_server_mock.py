import socket

def main():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('0.0.0.0', 8888))
    server_socket.listen(1)
    print("Servidor escuchando en el puerto 8888...")

    client_socket, client_address = server_socket.accept()
    print("Conexión establecida desde:", client_address)

    # Recibiendo la longitud del archivo
    # name_data = client_socket.recv(8)
    # image_name = int.from_bytes(name_data, byteorder='big')

    # Recibiendo la longitud del archivo
    size_data = client_socket.recv(8)
    image_size = int.from_bytes(size_data, byteorder='little')

    # Recibiendo la imagen en fragmentos y guardándola
    received_data = b''
    while len(received_data) < image_size:
        data = client_socket.recv(1024)
        if not data:
            break
        received_data += data

    # Guardando la imagen recibida en el servidor
    with open("received_image.jpg", "wb") as file:
        file.write(received_data)

    print("Imagen recibida y guardada.")

    # Leyendo la imagen del servidor y enviándola de vuelta al cliente
    with open("received_image.jpg", "rb") as file:
        image_data = file.read()

    # Enviando la longitud de la imagen al cliente
    client_socket.send(str(len(image_data)).encode())

    # Enviando la imagen al cliente en fragmentos
    for i in range(0, len(image_data), 1024):
        client_socket.send(image_data[i:i+1024])

    print("Imagen enviada de vuelta al cliente.")

    client_socket.close()
    server_socket.close()

if __name__ == "__main__":
    main()