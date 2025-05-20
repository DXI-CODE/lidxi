#pragma once
#include "class_knn.h"
#include <stdlib.h>

void put_in_array(JEF *jef_i, unsigned char id_candidato){
    jef_i->cont = 1;
    jef_i->id = id_candidato;
}

void sum_elem_array(JEF *jef_i, unsigned char id_candidato){
    jef_i->cont = jef_i->cont + 1;
    jef_i->id = id_candidato;
}


short is_in_array(JEF *jef, unsigned char id, unsigned int arr_size){
    unsigned char i = 0;
    if(jef == NULL || arr_size == 0) return -1;

    for(i=0; i < arr_size; i++){
        if(jef[i].id == id)
            return i;
    }
    return -1;
}

void printf_boss(JEF *jef, unsigned int tam){
    unsigned int i;
    Serial.println("boss: ");
    for(i=0; i < tam; i++){
        Serial.println("(cont: %u : id: %hhu), ", jef[i].cont, jef[i].id);
    }
    Serial.println("");
}
