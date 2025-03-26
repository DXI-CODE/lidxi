#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

#define K 7

typedef struct data{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char id;
}POINT;

typedef struct mayor{
	float distance;
	unsigned char id;
}MAY;

POINT *p;
MAY *may;
unsigned int lineas = 0;


float calculate_distance(POINT *p1, POINT *p2, float *distance){
	*distance = sqrt( pow((p2->r)-(p1->r),2) + pow((p2->g)-(p1->g), 2) + pow((p2->b)-(p1->b), 2));
	return *distance;
}

void change_boss(MAY *new_boss, unsigned int *k){
	MAY mayor_item;
	mayor_item.distance = may[0].distance;
	mayor_item.id = may[0].id;
	unsigned char intercambio = 0;
	for(*k = 0; *k < K; *k = (*k) + 1){
		if(may[*k].distance < mayor_item.distance){
			may[*k].distance = mayor_item.distance;
			may[*k].id = mayor_item.id;
			intercambio = 1;
		}
	}
	
	if( !intercambio){
		may[0].distance = mayor_item.distance;
		may[0].id = mayor_item.id;
	}
	
	new_boss->distance = mayor_item.distance;
	new_boss->id = mayor_item.id;
}

void predecir(POINT *predict){
	unsigned int i=0,j=0,k=0; //esto despues va ser necesario enviar como puntero a calculate_distance
	MAY mayor;
	float distance_item = 0.0;
	
	printf("\nImprimiendo las primeras %d distancias\n", K);
	
	for(i=0; i<K; i++){ //Aqui calculamos K distancias, seran las mas cortas por defecto
		may[i].distance = calculate_distance(p+i, predict, &may[i].distance);
		may[i].id = p[i].id;
		printf("%f : %hhu\n", may[i].distance, may[i].id);
	}
	
	//Aqui luego debemos mandar a llamar iterativamente desde k hasta n (siendo n el tamaño de lineas leidas)
	//Despues, volvemos a calular las distancias, y si encontramos uno menor en may[i], entonces lo remplazamos
	//por el mas grande del array may[]
	printf("\nImprimiendo distancias... lineas = %d", lineas);
	for(i=k; i<lineas; i++){
		calculate_distance(predict, p+i, &distance_item);
		printf("\nLa distancia entre (%hhu, %hhu, %hhu) y (%hhu, %hhu, %hhu) es de : %f", 
									predict->r, predict->g, predict->b, 
									p[i].r, p[i].g, p[i].b, 
									distance_item							
		);
		for(j=0; j<K; j++){
			if( may[j].distance > distance_item){
				MAY may_temp;
				may_temp.distance = distance_item;
				may_temp.id = p[i].id;
				change_boss(&may_temp, &k);
				break;
			}
		}
	}
	
	printf("\nEstos son los puntos mas cercanos: ");
	for(i=0; i<K; i++){
		printf("%f %hhu\n", may[i].distance, may[i].id);
	}
	
}

int main(int argc, char *argv[]) {
	
	p = calloc(1, sizeof(POINT));
	may = (MAY *) calloc(K, sizeof(MAY));
	
	unsigned short i=1,j,k;
	unsigned char r,g,b;
	
	FILE *data = fopen("final_data_colors.csv", "r");
	if(data == NULL){
		perror("ERROR: the file could not be read");
		return -1;
	}
	char *line = (char *) calloc(64, sizeof(char));
	
	while(fgets(line, 64, data)){ //this will run until the end of the file is reached.
		p = (POINT *) realloc((void*) p, sizeof(POINT) * 1 * i);
		
        if (sscanf(line, "%hhu,%hhu,%hhu,%hhu", &p[i-1].r, &p[i-1].g, &p[i-1].b, &p[i-1].id) != 4) {
            fprintf(stderr, "ERROR: linea mal formateada: %s\n", line);
			continue;
        }
		lineas++;
        
		i++;
	}
	printf("\nPude leer exitosamente los datos\n");
	printf("\nDatos obtenidos:\n");
	for(j=0; j<i-1; j++){
		printf("%hhu %hhu %hhu %hhu\n", (*(p+j)).r, (*(p+j)).g, (*(p+j)).b, (*(p+j)).id);
	}

	POINT predict;
	predict.r = 120;
	predict.g = 190;
	predict.b = 64;
	predecir(&predict);
	
	fclose(data);
    free(line);
    free(p);
    fclose(data);
	
	return 0;
}