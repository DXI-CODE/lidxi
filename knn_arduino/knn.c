#include <SD.h>
#include <SPI.h>
#include <stdlib.h>
#include <strings.h>

/*Library for KNN */
#include "class_knn.h"
#include "model.h"

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
            //f//printf(stderr, "ERROR: linea mal formateada: %s\n", line);
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
