#pragma once
#include <cstdint>
#include <stdint.h>
#define K 5
#define N 3

typedef struct data{
  int16_t data[N];
  uint8_t id;
}POINT;

typedef struct mayor{
  uint16_t distance;
  unsigned char id;
}MAY;

typedef struct jefes{
    uint8_t cont;
    uint8_t id;
}JEF;

POINT *p; //Conjunto de puntos (dataset)
MAY may[K]; //Conjunto de menores distancias
