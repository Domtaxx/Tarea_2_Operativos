import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageTk
from socket_cliente import socket_send_image
import io

def set_new_image_name(image_path):
    global new_image_name
    new_image_name = image_path.split("/")[-1]

def cargar_imagen():
    ruta_imagen = filedialog.askopenfilename()
    if ruta_imagen:
        imagen = Image.open(ruta_imagen)
        set_new_image_name(ruta_imagen)
        imagen.save(path_to_images + new_image_name)
        imagen = ImageTk.PhotoImage(imagen)
        lista_imagenes[new_image_name] = imagen
        actualizar_lista()

def obtenerIndiceImagenSeleccionada():
    indice_seleccionado = lista_box.curselection()
    if indice_seleccionado:
        indice_seleccionado = lista_box.curselection()
        indice = int(indice_seleccionado[0])
    else:
        indice = 0
    return indice

def set_histo():
    global funcion
    funcion = "hist"
    func_label.config(text="Modo: " + funcion)


def set_color():
    global funcion
    funcion = "cols"
    func_label.config(text="Modo: " + funcion)
        

def mostrar_imagen_seleccionada(event):
    indice = obtenerIndiceImagenSeleccionada()
    if indice < len(lista_imagenes):
        imagen_seleccionada = list(lista_imagenes.values())[indice]
        image_label.config(image=imagen_seleccionada)
        image_label.image = imagen_seleccionada
    else:
        image_label.config(image="")

def delete_image(indice):
    i = 0
    for key in lista_imagenes.keys():
        if i == indice: #assuming you want to remove the second element from the dictionary
            key_to_delete = key
        i = i + 1
    if key_to_delete in lista_imagenes: del lista_imagenes[key_to_delete]

def enviar_imagen():
    indice_seleccionado = lista_box.curselection()
    if indice_seleccionado:
        indice = int(indice_seleccionado[0])
        tk_imagen = list(lista_imagenes.values())[indice]
        delete_image(indice)
        actualizar_lista()
        image_label.config(image="")
        img = ImageTk.getimage(tk_imagen)
    mostrar_imagen_seleccionada(None)
    socket_send_image(ip_entry.get(), int(port_entry.get()), new_image_name)

def actualizar_lista():
    lista_box.delete(0, tk.END)
    for img_name in lista_imagenes:
        lista_box.insert(tk.END, f"{img_name}")

path_to_images = "Python/Client/ClientImages/"
new_image_name = ""
funcion = "hist"

# Crear ventana principal
ventana = tk.Tk()
ventana.title("Cargar y Ordenar Imágenes")

ip_label = tk.Label(ventana, text="IP: ")
ip_label.grid(row=0, column=0)


ip_entry = tk.Entry(ventana)
ip_entry.insert(0, "192.168.0.21")
ip_entry.grid(row=0, column=1)

port_label = tk.Label(ventana, text="Port: ")
port_label.grid(row=0, column=2)

port_entry = tk.Entry(ventana)
port_entry.insert(0, "1717")
port_entry.grid(row=0, column=3)

boton_cargar = tk.Button(ventana, text="Cargar Imagen", command=cargar_imagen)
boton_cargar.grid(row = 1, column=0, pady=10)

boton_enviar = tk.Button(ventana, text="Enviar Imagen", command=enviar_imagen)
boton_enviar.grid(row = 2, column=0, padx=10, pady=10)

boton_histo = tk.Button(ventana, text="Modo hist", command=set_histo)
boton_histo.grid(row = 3, column=0, padx=10, pady=10)

boton_color = tk.Button(ventana, text="Modo clas", command=set_color)
boton_color.grid(row = 4, column=0, padx=10, pady=10)

func_label = tk.Label(ventana, text= "Modo: " + funcion)
func_label.grid(row=5, column=2)

lista_box = tk.Listbox(ventana)
lista_box.grid(row = 1, column=1, rowspan=2)

lista_box.bind("<<ListboxSelect>>", mostrar_imagen_seleccionada)

# Lista para almacenar las imágenes cargadas
# lista_imagenes = []
lista_imagenes = {}

# Crear etiqueta para mostrar la imagen seleccionada
image_label = tk.Label(ventana)
image_label.grid(row=6, column=0, columnspan=4)

# Iniciar bucle principal
ventana.mainloop()