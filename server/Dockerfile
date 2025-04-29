# Imagen base de Python
FROM python:3.11-slim

# Establece el directorio de trabajo
WORKDIR /app

# Copia el archivo requirements.txt y luego instala las dependencias
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Copia el archivo app.py al contenedor
COPY app.py .

# Crea la carpeta /data y copia el archivo CSV al contenedor
RUN mkdir -p /data
COPY latest.csv /data/latest.csv

# Exponer el puerto 7001
EXPOSE 7001

# Comando para correr la aplicación Flask
CMD ["python", "app.py"]
