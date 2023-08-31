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
    size_data = client_socket.recv(4)
    image_size = int(size_data.decode())

    client_socket.recv(1) #El servidor recibe el caracter de separación

    # Recibiendo la imagen en fragmentos y guardándola
    received_data = b''
    while len(received_data) < image_size:
        data = client_socket.recv(4096)
        if not data:
            break
        received_data += data

    # Guardando la imagen recibida en el servidor
    with open("received_image.png", "wb") as file:
        file.write(received_data)

    print("Imagen recibida y guardada.")
    
    client_socket.close()
    server_socket.close()

if __name__ == "__main__":
    while True:
        main()