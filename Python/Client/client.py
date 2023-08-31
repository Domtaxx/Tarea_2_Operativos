import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageTk
from socket_cliente import socket_send_image
import io

def image_to_bytes(pil_image):
    image_stream = io.BytesIO()
    pil_image.save(image_stream, format='PNG')
    image_bytes = image_stream.getvalue()
    return image_bytes

def set_new_image_name(image_path):
    global new_image_name
    new_image_name = image_path.split("/")[-1]

def cargar_imagen():
    ruta_imagen = filedialog.askopenfilename()
    if ruta_imagen:
        imagen = Image.open(ruta_imagen)
        # save image with original name
        set_new_image_name(ruta_imagen)
        imagen.save(path_to_images + new_image_name)
        imagen = ImageTk.PhotoImage(imagen)
        lista_imagenes.append(imagen)
        ordenar_por_tamano()
        actualizar_lista()

def obtenerIndiceImagenSeleccionada():
    indice_seleccionado = lista_box.curselection()
    if indice_seleccionado:
        indice_seleccionado = lista_box.curselection()
        indice = int(indice_seleccionado[0])
    else:
        indice = 0
    return indice

def mostrar_imagen_seleccionada(event):
    indice = obtenerIndiceImagenSeleccionada()
    if indice < len(lista_imagenes):
        imagen_seleccionada = lista_imagenes[indice]
        label_imagen.config(image=imagen_seleccionada)
        label_imagen.image = imagen_seleccionada
    else:
        label_imagen.config(image="")

def ordenar_por_tamano():
    lista_imagenes.sort(key=lambda img: img.width() * img.height())
    actualizar_lista()

def mostrar_imagen_del_server(tk_imagen):
    label_imagen_server.config(image=tk_imagen)
    label_imagen_server.image = tk_imagen

def enviar_imagen():
    indice_seleccionado = lista_box.curselection()
    if indice_seleccionado:
        indice = int(indice_seleccionado[0])
        tk_imagen = lista_imagenes.pop(indice)
        actualizar_lista()
        label_imagen.config(image="")
        img = ImageTk.getimage(tk_imagen)
        print(type(img))
    mostrar_imagen_seleccionada(None)
    mostrar_imagen_del_server(tk_imagen)
    socket_send_image(ip_entry.get(), int(port_entry.get()), new_image_name)

def actualizar_lista():
    lista_box.delete(0, tk.END)
    for i, imagen in enumerate(lista_imagenes):
        lista_box.insert(tk.END, f"{new_image_name}")

path_to_images = "Python/Client/ClientImages/"
new_image_name = ""

# Crear ventana principal
ventana = tk.Tk()
ventana.title("Cargar y Ordenar Imágenes")

ip_label = tk.Label(ventana, text="IP: ")
ip_label.grid(row=0, column=0)

ip_entry = tk.Entry(ventana)
ip_entry.insert(0, "127.0.0.1")
ip_entry.grid(row=0, column=1)

port_label = tk.Label(ventana, text="Port: ")
port_label.grid(row=0, column=2)

port_entry = tk.Entry(ventana)
port_entry.insert(0, "8888")
port_entry.grid(row=0, column=3)


# Crear botones y lista
boton_cargar = tk.Button(ventana, text="Cargar Imagen", command=cargar_imagen)
boton_cargar.grid(row = 1, column=0, pady=10)

boton_enviar = tk.Button(ventana, text="Enviar Imagen", command=enviar_imagen)
boton_enviar.grid(row = 2, column=0, padx=10, pady=10)

lista_box = tk.Listbox(ventana)
lista_box.grid(row = 1, column=1, rowspan=2)

lista_box.bind("<<ListboxSelect>>", mostrar_imagen_seleccionada)

# Lista para almacenar las imágenes cargadas
lista_imagenes = []

# Crear etiqueta para mostrar la imagen seleccionada
label_imagen = tk.Label(ventana)
label_imagen.grid(row=3, column=0)

label_imagen_server = tk.Label(ventana)
label_imagen_server.grid(row=4, column=1)

# Iniciar bucle principal
ventana.mainloop()