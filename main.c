#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h> 

#define K 7
#define N 3

typedef struct data{
  short data[N];
  unsigned char id;
}POINTT;

typedef struct mayor{
  unsigned int distance;
  unsigned char id;
}MAY;

POINTT *p;
MAY *may;
unsigned int lineas = 0;


unsigned int calculate_distance(POINTT *p1, POINTT *p2, unsigned int *distance){
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

void predecir(POINTT *predict){
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
  
}

int main(int argc, char *argv[]) {
  
	p = calloc(1, sizeof(POINTT));
	may = (MAY *) calloc(K, sizeof(MAY));
	unsigned short i=1,j;
  
	FILE *data = fopen("final_data_colors.csv", "r");
	if(data == NULL){
    	perror("ERROR: the file could not be read");
    	return -1;
  	}
	char *line = (char *) calloc(64, sizeof(char));
	
	while(fgets(line, 64, data)){ //this will run until the end of the file is reached.
    	p = (POINTT *) realloc((void*) p, sizeof(POINTT) * 1 * i);
		if (sscanf(line, "%hd,%hd,%hd,%hd", &p[i-1].data[0], &p[i-1].data[1], &p[i-1].data[2], &p[i-1].id) != 4) {
            //fprintf(stderr, "ERROR: linea mal formateada: %s\n", line);
			continue;
		}
    	lineas++;
        i++;
	}
	printf("\nAviso: Pude leer exitosamente los datos\n");
	printf("\nDatos obtenidos:\n");
	for(j=0; j<i-1; j++){
		printf("%hd %hd %hd %hhu\n", (*(p+j)).data[0], (*(p+j)).data[1], (*(p+j)).data[2], (*(p+j)).id);
	}
  
	POINTT predict;
  
	while(1){
    	predict.data[0] = rand() % 256;
    	predict.data[1] = rand() % 256;
    	predict.data[2] = rand() % 256;
    	Sleep(1000);
		predecir(&predict); 
	}
    
	fclose(data);
	free(line);
    free(p);
    fclose(data);
  
  return 0;
}