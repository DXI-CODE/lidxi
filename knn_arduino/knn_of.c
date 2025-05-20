#include <SPI.h>
#include <SD.h>
#include <cstdint>
#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"


#define MAXPUNTOS 1000
#define CS_PIN 10  // PB2 es el pin digital 10 en Arduino



#define SENSOR_PIN0 A1
#define SENSOR_PIN1 A2
#define SENSOR_PIN2 A3
#define SENSOR_PIN3 A4
#define SENSOR_PIN4 A5


#define CAPTURAR_PIN 2
MPU6050 sensor(0x68);
int16_t gx, gy, gz;

// Escala para convertir los valores raw a unidades físicas (°/s)
const int gyroScale = 131;  // Para ±250°/s
POINT predict;

void setup() {
    Serial.begin(9600);
    Serial.println("Iniciando SD...");

    p = calloc(1, sizeof(POINT));
	uint8_t i=1,j;

    //Sensore FLEX
    pinMode(SENSOR_PIN0, INPUT);
    pinMode(SENSOR_PIN1, INPUT);
    pinMode(SENSOR_PIN2, INPUT);
    pinMode(SENSOR_PIN3, INPUT);
    pinMode(SENSOR_PIN4, INPUT);
    pinMode(CAPTURAR_PIN, INPUT_PULLUP);


    if (!SD.begin(CS_PIN)) {
        Serial.println("Error al iniciar la tarjeta SD");
        return;
    }

    Serial.println("Tarjeta SD inicializada correctamente");
    File archivo = SD.open("data.csv");

    if (archivo) {
        int i = 0;
        Serial.println("Leyendo datos desde CSV...");

        while (archivo.available() && i < MAX_PUNTOS) {
        String linea = archivo.readStringUntil('\n');
        linea.trim();

        if (linea.length() == 0) continue;

        // Dividir la línea por comas
        int pos = 0;
        int lastIndex = 0;
        String valores[9];

        for (int j = 0; j < 8; j++) {
            pos = linea.indexOf(',', lastIndex);
            if (pos == -1) {
                Serial.print("Línea mal formateada: ");
                Serial.println(linea);
                break;
            }
            valores[j] = linea.substring(lastIndex, pos);
            lastIndex = pos + 1;
        }

        valores[8] = linea.substring(lastIndex);

        bool lineaValida = true;
        for (int j = 0; j < 9; j++) {
            if (valores[j].length() == 0) {
                lineaValida = false;
                break;
            }
        }

        if (!lineaValida) {
            Serial.print("Línea incompleta o mal formateada: ");
            Serial.println(linea);
            continue;
        }

        // Asigna los valores al struct
        for (int j = 0; j < 8; j++) {
            p[i].data[j] = valores[j].toInt();
        }
        p[i].id = valores[8].toInt();
        i++;
    }

    lineas = i;
    archivo.close();
    Serial.print("Total de puntos cargados: ");
    Serial.println(lineas);
  } else {
    Serial.println("Error al leer archivo.");
  }

    //SENSORES GIROSCOPIO
    Wire.begin();         // Iniciar comunicación I2C
    sensor.initialize();
    sensor.setSleepEnabled(false);

    if (sensor.testConnection()) {
      Serial.println("Sensor iniciado correctamente");
    } else {
      Serial.println("Error al iniciar el sensor");
      while (1);
    }


}

void loop() {
  // Nada por ahora
  if (digitalRead(CAPTURAR_PIN) == HIGH) { //Se preciona y se activa el sensor, si se presiona otra vez se apaga el sensor. En caso de solo querer el dato al momento cambiar a LOW.

      //sensor giroscopio
      sensor.getRotation(&gx, &gy, &gz);
      int16_t gx = (gx / gyroScale) * 100;
      int16_t gy = (gy / gyroScale) * 100;
      int16_t gz = (gz / gyroScale) * 100;

      /*Sensores flex */
      predict.data[0] = analogRead(SENSOR_PIN0);
      predict.data[1] = analogRead(SENSOR_PIN1);
      predict.data[2] = analogRead(SENSOR_PIN2);
      predict.data[3] = analogRead(SENSOR_PIN3);
      predict.data[4] = analogRead(SENSOR_PIN4);
      /*Sensores flex */

      predict.data[5] = gx;
      predict.data[6] = gy;
      predict.data[7] = gz;
      predict.data[8] = ID_ELEGIDO;



      Serial.print(predict.data[0]); Serial.print(",");
      Serial.print(predict.data[1]); Serial.print(",");
      Serial.print(predict.data[2]); Serial.print(",");
      Serial.print(predict.data[3]); Serial.print(",");
      Serial.print(predict.data[4]); Serial.print(",");
      Serial.print(predict.data[5]); Serial.print(",");
      Serial.print(predict.data[6]); Serial.print(",");
      Serial.print(predict.data[7]); Serial.print(",");
      Serial.print(predict.data[8]); Serial.print(",");
      Serial.println();

      delay(3000);
  }
}
