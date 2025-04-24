#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

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

void printf_arr(){
    int i;
    printf("\nmay: ");
    for(i=0; i < K; i++){
        printf("(dist: %d : id: %d), ", may[i].distance, may[i].id);
    }
    printf("\n");
}

void printf_boss(JEF *jef, unsigned int tam){
    int i;
    printf("\nboss: ");
    for(i=0; i < tam; i++){
        printf("(cont: %u : id: %hhu), ", jef[i].cont, jef[i].id);
    }
    printf("\n");
}

void merge(JEF *arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    JEF *L = (JEF *) malloc(n1 * sizeof(JEF));
    JEF *R = (JEF *) malloc(n2 * sizeof(JEF));

    if (L == NULL || R == NULL) return;

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0; j = 0; k = left;

    // Orden descendente: mayor a menor
    while (i < n1 && j < n2) {
        if (L[i].cont >= R[j].cont) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(JEF *arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
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
    JEF jef[K]; //conjunto de jefes
    JEF boss;
    boss.cont = 0;//el mero chaka
    boss.id = 0;

    printf_arr();

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

    printf_boss(jef, cont_jc);
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
      //printf(" : %f", may[j].distance);
      if( distance_item < may[j].distance){
        may_temp.distance = distance_item;
        may_temp.id = p[i].id;
        change_boss(&may_temp);
        break;
      }
    }
  }

  printf("\nEstos son las %d etiquetas mas cercanas para (%hd %hd %hd): \n", K, predict->data[0], predict->data[1], predict->data[2]);
  for(i=0; i<K; i++){
    printf("%u %hhu\n", may[i].distance, may[i].id);
  }

  JEF jefe_final = get_boss();
  if(jefe_final.cont != 0){
    printf("%u votos ||  id: %hhu\n", jefe_final.cont, jefe_final.id);
  }
  else{
    printf("\nNo se pudo determinar la prediccion");
  }

}

int main(int argc, char *argv[]) {
	p = calloc(1, sizeof(POINT));
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
