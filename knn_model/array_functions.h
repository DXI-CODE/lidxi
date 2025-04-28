#pragma once
#include "class_knn.h"
#include <stdlib.h>
#include <stdio.h>

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

void printf_may(){
    unsigned int i;
    printf("\nmay: ");
    for(i=0; i < K; i++){
        printf("(dist: %d : id: %d), ", may[i].distance, may[i].id);
    }
    printf("\n");
}

void printf_boss(JEF *jef, unsigned int tam){
    unsigned int i;
    printf("\nboss: ");
    for(i=0; i < tam; i++){
        printf("(cont: %u : id: %hhu), ", jef[i].cont, jef[i].id);
    }
    printf("\n");
}
