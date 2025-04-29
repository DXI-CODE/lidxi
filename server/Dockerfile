# Imagen base
FROM python:3.11-slim

# Establece directorio de trabajo
WORKDIR /app

# Copia los archivos necesarios
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY app.py .
# Asegúrate de copiar también el directorio data si lo tienes ya
COPY data/ /data/

# Exponer puerto
EXPOSE 7000

# Comando para correr la app
CMD ["python", "app.py"]
