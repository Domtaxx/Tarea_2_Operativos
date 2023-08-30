import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageTk

def cargar_imagen():
    ruta_imagen = filedialog.askopenfilename()
    if ruta_imagen:
        imagen = Image.open(ruta_imagen)
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
        imagen = lista_imagenes.pop(indice)
        actualizar_lista()
        label_imagen.config(image="")
    mostrar_imagen_seleccionada(None)
    mostrar_imagen_del_server(imagen)

def actualizar_lista():
    lista_box.delete(0, tk.END)
    for i, imagen in enumerate(lista_imagenes):
        lista_box.insert(tk.END, f"Imagen {i+1} - {imagen.width()}x{imagen.height()}")

# Crear ventana principal
ventana = tk.Tk()
ventana.title("Cargar y Ordenar Imágenes")

# Crear botones y lista
boton_cargar = tk.Button(ventana, text="Cargar Imagen", command=cargar_imagen)
boton_cargar.grid(row = 0, column=0, pady=10)

boton_enviar = tk.Button(ventana, text="Enviar Imagen", command=enviar_imagen)
boton_enviar.grid(row = 1, column=0, padx=10, pady=10)

lista_box = tk.Listbox(ventana)
lista_box.grid(row = 0, column=1, rowspan=2)

lista_box.bind("<<ListboxSelect>>", mostrar_imagen_seleccionada)

# Lista para almacenar las imágenes cargadas
lista_imagenes = []

# Crear etiqueta para mostrar la imagen seleccionada
label_imagen = tk.Label(ventana)
label_imagen.grid(row=2, column=0)

label_imagen_server = tk.Label(ventana)
label_imagen_server.grid(row=2, column=1)

# Iniciar bucle principal
ventana.mainloop()