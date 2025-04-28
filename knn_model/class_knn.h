#pragma once
#define K 5
#define N 3

typedef struct data{
  short data[N];
  unsigned char id;
}POINT;

typedef struct mayor{
  unsigned int distance;
  unsigned char id;
}MAY;

typedef struct jefes{
    unsigned int cont;
    unsigned char id;
}JEF;

POINT *p; //Conjunto de puntos (dataset)
MAY may[K]; //Conjunto de menores distancias
