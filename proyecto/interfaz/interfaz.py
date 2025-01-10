import tkinter as tk
from tkinter import Canvas
from PIL import Image, ImageTk
import serial
import threading
import os

# Crear ventana principal
root = tk.Tk()
root.title("Interfaz con Medidores e Imágenes")
root.geometry("900x650")
root.configure(bg="#2c2f33")

# Crear frames para organizar contenido
frame_images = tk.Frame(root, bg="#2c2f33")
frame_images.pack(pady=20)

frame_meters = tk.Frame(root, bg="#2c2f33")
frame_meters.pack(pady=20)


# Función para crear un medidor personalizado
def create_custom_meter(parent, title):
    frame = tk.Frame(parent, bg="#2c2f33")
    frame.pack(side=tk.LEFT, padx=20)

    label = tk.Label(
        frame, text=title, font=("Arial", 14, "bold"), fg="#ffffff", bg="#2c2f33"
    )
    label.pack(pady=5)

    canvas = Canvas(frame, width=100, height=250, bg="#2c2f33", highlightthickness=0)
    canvas.pack(pady=10)

    # Dibujar el fondo del medidor
    canvas.create_rectangle(40, 20, 60, 230, fill="#23272a", outline="")

    # Crear barra dinámica
    bar = canvas.create_rectangle(40, 230, 60, 230, fill="#7289da", outline="")

    value_label = tk.Label(
        frame, text="0%", font=("Arial", 12), fg="#ffffff", bg="#2c2f33"
    )
    value_label.pack(pady=5)

    return canvas, bar, value_label

def create_temperature_custom_meter(parent, title):
    frame = tk.Frame(parent, bg="#2c2f33")
    frame.pack(side=tk.LEFT, padx=20)

    label = tk.Label(
        frame, text=title, font=("Arial", 14, "bold"), fg="#ffffff", bg="#2c2f33"
    )
    label.pack(pady=5)

    canvas = Canvas(frame, width=100, height=250, bg="#2c2f33", highlightthickness=0)
    canvas.pack(pady=10)

    # Dibujar el fondo del medidor
    canvas.create_rectangle(40, 20, 60, 230, fill="#23272a", outline="")

    # Crear barra dinámica
    bar = canvas.create_rectangle(40, 230, 60, 230, fill="#7289da", outline="")

    value_label = tk.Label(
        frame, text="0°C", font=("Arial", 12), fg="#ffffff", bg="#2c2f33"
    )
    value_label.pack(pady=5)

    return canvas, bar, value_label


# Función para actualizar el medidor
def update_custom_meter(canvas, bar, value_label, value, max_value=100):
    if value > max_value:
        value = max_value
    height = 210 * (value / max_value)
    canvas.coords(bar, 40, 230 - height, 60, 230)
    value_label.config(text=f"{value}%")

def update_light_meter(canvas, bar, value_label, value):
    max_value = 325
    if value > max_value:
        value = max_value
    height = 210 * (value / max_value)
    canvas.coords(bar, 40, 230 - height, 60, 230)
    percent = int((value / max_value) * 100)
    value_label.config(text=f"{percent}%")

def update_temperature_meter(canvas, bar, value_label, raw_value):
    # Mapea 63 -> 20°C, 264 -> 66°C
    if raw_value < 63:
        raw_value = 63
    if raw_value > 264:
        raw_value = 264
    celsius = 20 + (raw_value - 63) * (46 / (264 - 63))
    height = 210 * (celsius / 66)
    canvas.coords(bar, 40, 230 - height, 60, 230)
    value_label.config(text=f"{int(celsius)}°C")


# Cargar imágenes desde una carpeta
def load_images_from_folder(folder_path, count):
    images = []
    for i in range(count):
        file = os.path.join(folder_path, f"{folder_path.split('/')[-1]}_{i}.jpg")
        if os.path.exists(file):
            try:
                img = Image.open(file).resize((250, 200))
                images.append(ImageTk.PhotoImage(img))
            except Exception as e:
                print(f"Error cargando la imagen {file}: {e}")
        else:
            print(f"Imagen no encontrada: {file}")
    return images

def load_ter_images_from_folder(folder_path, count):
    images = []
    for i in range(count):
        file = os.path.join(folder_path, f"{folder_path.split('/')[-1]}_{i}.png")
        if os.path.exists(file):
            try:
                img = Image.open(file).resize((250, 200))
                images.append(ImageTk.PhotoImage(img))
            except Exception as e:
                print(f"Error cargando la imagen {file}: {e}")
        else:
            print(f"Imagen no encontrada: {file}")
    return images


# Función para seleccionar una imagen basada en el valor
def select_image(value, image_list, max_value=100):
    index = min(value * len(image_list) // (max_value + 1), len(image_list) - 1)
    return image_list[index]


# Cargar imágenes de cada tipo
termometro_images = load_ter_images_from_folder(
    "interfaz/media/termometro", 10
)
vaso_images = load_images_from_folder(
    "interfaz/media/vaso", 8
)
foco_images = load_ter_images_from_folder(
    "interfaz/media/foco", 8
)

# Crear etiquetas para mostrar imágenes
termometro_label = tk.Label(frame_images, bg="#2c2f33", borderwidth=2, relief="ridge")
termometro_label.pack(side=tk.LEFT, padx=10)

vaso_label = tk.Label(frame_images, bg="#2c2f33", borderwidth=2, relief="ridge")
vaso_label.pack(side=tk.LEFT, padx=10)

foco_label = tk.Label(frame_images, bg="#2c2f33", borderwidth=2, relief="ridge")
foco_label.pack(side=tk.LEFT, padx=10)

# Mostrar imágenes por defecto
if termometro_images:
    termometro_label.config(image=termometro_images[0])
if vaso_images:
    vaso_label.config(image=vaso_images[0])
if foco_images:
    foco_label.config(image=foco_images[0])

# Crear medidores personalizados
meter_temp, bar_temp, label_temp = create_temperature_custom_meter(frame_meters, "Temperatura")
meter_humidity, bar_humidity, label_humidity = create_custom_meter(
    frame_meters, "Humedad"
)
meter_light, bar_light, label_light = create_custom_meter(frame_meters, "Luz")


# Configuración del puerto serial con manejo de errores
def init_serial():
    try:
        port = "/dev/ttyUSB0"  # Cambia 'COM3' al puerto correcto
        baud_rate = 115200
        print(f"Intentando abrir el puerto serial {port} a {baud_rate}...")
        return serial.Serial(port, baud_rate, timeout=1)
    except serial.SerialException as e:
        print(f"Error al abrir el puerto serial: {e}")
        return None


serial_port = init_serial()


# Función para leer datos del puerto serial
def read_serial():
    if not serial_port:
        print("El puerto serial no está disponible. Deteniendo lectura.")
        return

    while True:
        try:
            line = serial_port.readline().decode("utf-8").strip()
            if line:
                try:
                    print(line)
                    temp_value, humidity_value, light_value = map(int, line.split(","))

                    # Actualizar medidores
                    update_temperature_meter(meter_temp, bar_temp, label_temp, temp_value)
                    update_custom_meter(
                        meter_humidity, bar_humidity, label_humidity, humidity_value
                    )
                    update_light_meter(meter_light, bar_light, label_light, light_value)

                    # Actualizar imágenes basadas en los valores
                    if termometro_images:  # 10 images, 0–66 range
                        termometro_label.config(image=select_image(temp_value, termometro_images, 66))
                        print(f"Termometro image level: {temp_value}")
                    if vaso_images:        # 8 images, 0–100 range
                        vaso_label.config(image=select_image(humidity_value, vaso_images, 100))
                        print(f"Vaso image level: {humidity_value}")
                    if foco_images:        # 8 images, 0–100 range
                        foco_label.config(image=select_image(light_value, foco_images, 100))
                        print(f"Foco image level: {light_value}")
                except ValueError as e:
                    print(f"Error al parsear los datos: {e}")
            else:
                print("No se recibieron datos.")
        except Exception as e:
            print(f"Error leyendo del puerto serial: {e}")


# Hilo para leer datos del puerto serial si el puerto está disponible
if serial_port:
    serial_thread = threading.Thread(target=read_serial, daemon=True)
    serial_thread.start()
else:
    print("No se inició el hilo porque el puerto serial no está disponible.")

# Iniciar bucle principal
root.mainloop()
