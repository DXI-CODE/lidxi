#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct string {
    char *ptr;
    size_t len;
};

void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(1);
    if (s->ptr == NULL) {
        fprintf(stderr, "No se pudo asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "No se pudo reasignar memoria\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr + s->len, ptr, size * nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;
    return size * nmemb;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <url> <version>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    const char *version = argv[2];

    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error al inicializar CURL\n");
        return 1;
    }

    struct string response;
    init_string(&response);

    // Crear JSON manualmente
    char json_data[128];
    snprintf(json_data, sizeof(json_data), "{\"version\":\"%s\"}", version);

    // Establecer headers
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() falló: %s\n", curl_easy_strerror(res));
    } else {
        // Decidir extensión de salida
        const char *ext = (strstr(response.ptr, ",") != NULL && strstr(response.ptr, "\n") != NULL) ? "csv" : "json";
        char filename[64];
        snprintf(filename, sizeof(filename), "respuesta.%s", ext);

        FILE *file = fopen(filename, "w");
        if (file) {
            fputs(response.ptr, file);
            fclose(file);
            printf("Respuesta guardada en %s\n", filename);
        } else {
            fprintf(stderr, "No se pudo guardar la respuesta\n");
        }
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    free(response.ptr);
    return 0;
}
