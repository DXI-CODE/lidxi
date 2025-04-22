#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#define K 7
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
MAY *may; //Conjunto de menores distancias

unsigned int lineas = 0;

unsigned int calculate_distance(POINT *p1, POINT *p2, unsigned int *distance){
	unsigned char i = 0;
	for(i=0; i<N; i++)
		*distance = (*distance) + abs(p2->data[i] - p1->data[i]);
	return *distance;
}

void change_boss(MAY *new_boss){
  MAY mayor_item;
  mayor_item.distance = may[0].distance;
  mayor_item.id = may[0].id;
  unsigned char k = 0;
  unsigned char may_index = 0;

  for(k = 0; k < K; k = k + 1){
    if(may[k].distance > mayor_item.distance){
      may_index = k;
    }
  }

  may[may_index].distance = new_boss->distance;
  may[may_index].id = new_boss->id;
}

void short_array(JEF *jef, int n) {
    unsigned int i,j;
    JEF temp;

    for (i = 1; i < n; i++) {
        temp = jef[i];
        j = i - 1;
        while (j >= 0 && jef[j].cont > temp.cont) {
            jef[j + 1] = jef[j];
            j--;
        }
        jef[j + 1] = temp;
    }
}

void put_in_array(JEF *jef_i, unsigned char id_candidato){
    jef_i->cont = 0;
    jef_i->id = id_candidato;
}

void sum_elem_array(JEF *jef_i, unsigned char id_candidato){
    jef_i->cont++;
    jef_i->id = id_candidato;
}


short is_in_array(JEF *jef, unsigned char id, unsigned int arr_size){
    unsigned char i = 0;
    for(i=0; i<arr_size; i++){
        if(jef[i].id == id)
            return i;
    }
    return -1;
}

JEF get_boss(){
    /*Esta es la función RH ya que todos querrán ser el candidato
    numero 1 para ser el jefe pero solo uno podrá ser el verdadero
    ** por defecto sabemos que hay K candidatos
    */

    //may = candidatos (un may, posible chaka) || jef = jefes (el chaka)
    //
    unsigned int cont_jc = 0;
    short pos = 0;
    unsigned char i;
    JEF *jef = NULL; //conjunto de jefes
    JEF boss; //el mero chaka

    for(i=0; i<K; i++){
        pos = is_in_array(jef, may[i].id, cont_jc);
        if(pos == -1){ //No esta en el array
            if (jef == NULL) {
                jef = (JEF *) calloc(cont_jc+1, sizeof(JEF));
            } else {
                jef = (JEF *) realloc(jef, (cont_jc+1) * sizeof(JEF));
            }
            put_in_array(&jef[cont_jc], may[i].id);
            cont_jc++;
        }
        else{
            sum_elem_array(&jef[pos], may[i].id);
        }
    }
    short_array(jef, cont_jc);
    boss.cont = jef[0].cont;
    boss.id = jef[0].id;
    free(jef);
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
      //printf(" : %f", may[j].distance);
      if( distance_item < may[j].distance){
        may_temp.distance = distance_item;
        may_temp.id = p[i].id;
        change_boss(&may_temp);
        break;
      }
    }
  }

  printf("\nEstos son las %d etiquetas mas cercanas para (%hhu %hhu %hhu): \n", K, predict->data[0], predict->data[1], predict->data[2]);
  for(i=0; i<K; i++){
    printf("%u %hhu\n", may[i].distance, may[i].id);
  }

  JEF jefe_final = get_boss();
  printf("%u votos ||  id: %hhu\n", jefe_final.cont, jefe_final.id);
}

int main(int argc, char *argv[]) {
	p = calloc(1, sizeof(POINT));
	may = (MAY *) calloc(K, sizeof(MAY));
	unsigned short i=1,j;

	FILE *data = fopen("final_data_colors.csv", "r");
	if(data == NULL){
    	perror("ERROR: the file could not be read");
    	return -1;
  	}
	char *line = (char *) calloc(64, sizeof(char));

	while(fgets(line, 64, data)){ //this will run until the end of the file is reached.
    	p = (POINT *) realloc((void*) p, sizeof(POINT) * 1 * i);
		if (sscanf(line, "%hd,%hd,%hd,%hhu", &p[i-1].data[0], &p[i-1].data[1], &p[i-1].data[2], &p[i-1].id) != 4) {
            //fprintf(stderr, "ERROR: linea mal formateada: %s\n", line);
			continue;
		}
    	lineas++;
        i++;
	}

	POINT predict;

	while(1){
    	predict.data[0] = rand() % 256;
    	predict.data[1] = rand() % 256;
    	predict.data[2] = rand() % 256;
    	sleep(2);
		predecir(&predict);
	}

	fclose(data);
	free(line);
    free(p);

  return 0;
}
