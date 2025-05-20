#include <SPI.h>
#include <SD.h>
#include <cstdint>

#define MAXPUNTOS 1000
#define CS_PIN 10  // PB2 es el pin digital 10 en Arduino

void setup() {

    p = calloc(1, sizeof(POINT));
	uint8_t i=1,j;

    Serial.begin(9600);
    Serial.println("Iniciando SD...");

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

        // El último valor (id)
        valores[8] = linea.substring(lastIndex);

        // Verifica que se hayan extraído los 9 valores
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


}

void loop() {
  // Nada por ahora
}
