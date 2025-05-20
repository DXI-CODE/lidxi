import serial
import csv
import os

archivo_salida = "datos.csv"

try:
    # Abrir el puerto COM10 con baudrate 9600
    ser = serial.Serial("COM10", 9600, timeout=1)
    print(f"Puerto {ser.port} abierto correctamente.")
    
    # Verificar si el archivo ya existe para no escribir los encabezados nuevamente
    existe_archivo = os.path.exists(archivo_salida)

    # Abrir archivo CSV en modo "a" (append: añadir datos sin sobrescribir)
    with open(archivo_salida, mode="a", newline="") as archivo:
        writer = csv.writer(archivo)

        # Si el archivo es nuevo, escribir los encabezados
        if not existe_archivo:
            writer.writerow(["Sensor1", "Sensor2", "Sensor3", "Sensor4", "Sensor5", "GiroX", "GiroY", "GiroZ"])


        # Leer datos del Arduino y agregarlos al CSV
        while True:
            data = ser.readline().decode().strip()  # Leer línea y decodificar
            if data:
                valores = data.split(",")  # Separar valores por ","
                if len(valores) == 8:  # Asegurar que sean 5 valores (según tu Arduino)
                    print("Datos recibidos:", valores)
                    writer.writerow(valores)  # Agregar al CSV
                    archivo.flush()  # Forzar escritura en disco

except serial.SerialException as e:
    print("Error al abrir el puerto COM:", e)

except KeyboardInterrupt:
    print("\nProceso detenido por el usuario.")

finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()
        print("Puerto cerrado.")
