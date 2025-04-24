#pragma once
#include "class_knn.h"
#include "array_functions.h"
#include "merge.h"

unsigned int lineas = 0;

unsigned int calculate_distance(POINT *p1, POINT *p2, unsigned int *distance){
	unsigned char i = 0;
	for(i=0; i < N; i++)
		*distance = (*distance) + abs(p2->data[i] - p1->data[i]);
	return *distance;
}

void change_boss(MAY *new_boss){
  unsigned char i = 0, may_index = 0;
  MAY mayor_item;
  mayor_item.distance = may[0].distance;
  mayor_item.id = may[0].id;

  for(i = 0; i < K; i = i + 1){
    if(may[i].distance > mayor_item.distance){
      may_index = i;
    }
  }

  may[may_index].distance = new_boss->distance;
  may[may_index].id = new_boss->id;
}


JEF get_boss(){ //Obtener la clasificación
    unsigned int cont_jc = 0, i;
    short pos = 0;
    JEF jef[K], boss;

    boss.cont = 0;
    boss.id = 0;

    for(i=0; i < K; i++){
        pos = is_in_array(jef, may[i].id, cont_jc);
        if(pos == -1){ //No esta en el array
            put_in_array(&jef[cont_jc], may[i].id);
            cont_jc++;
        }
        else{
            sum_elem_array(&jef[pos], may[i].id);
        }
    }

    merge_sort(jef, 0, cont_jc - 1);

    boss.cont = jef[0].cont;
    boss.id = jef[0].id;
    return boss;
}

void predecir(POINT *predict){
  unsigned int i=0,j=0,k=0;
  MAY may_temp;
  unsigned int distance_item = 0;


  for(i=0; i<K; i++){ //Aqui calculamos K distancias, seran las mas cortas por defecto
    may[i].distance = calculate_distance(p+i, predict, &may[i].distance);
    may[i].id = p[i].id;
  }

  /*Aqui luego debemos mandar a llamar iterativamente desde k hasta n (siendo n el tamaño de lineas leidas)
  Despues, volvemos a calular las distancias, y si encontramos uno menor en may[i], entonces lo remplazamos
  por el mas grande del array may[]*/

  for(i=k; i<lineas; i++){
  	distance_item = 0;
    calculate_distance(predict, p+i, &distance_item);
    for(j=0; j<K; j++){
      if( distance_item < may[j].distance){
        may_temp.distance = distance_item;
        may_temp.id = p[i].id;
        change_boss(&may_temp);
        break;
      }
    }
  }

  JEF jefe_final = get_boss();
  if(jefe_final.cont != 0){
    printf("%u votos ||  id: %hhu\n", jefe_final.cont, jefe_final.id);
  }
}
