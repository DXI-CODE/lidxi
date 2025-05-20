#include <SPI.h>
#include <SD.h>

#define CS_PIN 10  // PB2 es el pin digital 10 en Arduino

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando SD...");

  if (!SD.begin(CS_PIN)) {
    Serial.println("Error al iniciar la tarjeta SD");
    return;
  }

  Serial.println("Tarjeta SD inicializada correctamente");

  File archivo = SD.open("demo.txt", FILE_WRITE);
  if (archivo) {
    archivo.println("¡Hola desde Proteus!");
    archivo.close();
    Serial.println("Archivo escrito.");
  } else {
    Serial.println("Error al escribir archivo.");
  }

  archivo = SD.open("demo.txt");
  if (archivo) {
    Serial.println("Contenido de demo.txt:");
    while (archivo.available()) {
      Serial.write(archivo.read());
    }
    archivo.close();
  } else {
    Serial.println("Error al leer archivo.");
  }
}

void loop() {
  // Nada por ahora
}
