#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

#define K 11

typedef struct data{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	char label[16];
}POINT;

int main(int argc, char *argv[]) {
	
	POINT *p = calloc(1, sizeof(POINT));
	unsigned short i=1,j,k;
	unsigned char r,g,b;
	
	float distancias[K];
	
	FILE *data = fopen("final_data_colors.csv", "r");
	if(data == NULL){
		perror("ERROR: the file could not be read");
		return -1;
	}
	char *line = (char *) calloc(64, sizeof(char));
	
	while(fgets(line, 64, data)){ //this will run until the end of the file is reached.
		p = (POINT *) realloc((void*) p, sizeof(POINT) * 1 * i);
		
        if (sscanf(line, "%hhu,%hhu,%hhu,%15s", &p[i-1].r, &p[i-1].g, &p[i-1].b, p[i-1].label) != 4) {
            fprintf(stderr, "ERROR: linea mal formateada: %s\n", line);
            continue;
        }
        
		i++;
	}
	printf("\nPude leer exitosamente los datos\n");
	printf("\nDatos obtenidos:\n");
	for(j=0; j<i-1; j++){
		printf("%hhu %hhu %hhu %s\n", (*(p+j)).r, (*(p+j)).g, (*(p+j)).b, (*(p+j)).label);
	}
	
	printf("\nIntroduce los valores rgb a predecir: ");
	printf("\nEscribe el valor de r: ");
	scanf("%hhu", &r);
	printf("\nEscribe el valor de g: ");
	scanf("%hhu", &g);
	printf("\nEscribe el valor de b: ");
	scanf("%hhu", &b);
	
	printf("\nLos valores que quieres buscar son: %hhu, %hhu, %hhu", r, g, b);
	/*
	for(j=0; j<10; j++){
		distancias[j] = calcular_distancia(*(p+j)).r, *(p+j)).g, *(p+j)).b);
		p_aux[j] = p+j;
	}
	
	for(j=10; j<i-1; j++){
		for(k=0; k<10; k++){
			if(distancias[k] > calcular_distancia( (*(p+j)).r, (*(p+j)).g, (*(p+j)).b){
				
				break;
			}
		}
	}*/
	
	fclose(data);
    free(line);
    free(p);
    fclose(data);
	
	return 0;
}