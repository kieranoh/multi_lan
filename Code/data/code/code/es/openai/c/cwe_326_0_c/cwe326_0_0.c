#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    // Definimos la longitud de la clave RSA
    const int key_length = 2048; // Puedes modificarlo según tus necesidades

    // Comando para generar la clave RSA
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    // Ejecutamos el comando y redirigimos la salida a un archivo temporal
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Error al ejecutar el comando
    }

    // Leemos la clave generada desde el flujo
    char *private_key = NULL;
    size_t length = 0;
    ssize_t read;

    // Usamos un buffer temporal para capturar la salida
    size_t buffer_size = 1024;
    private_key = (char *)malloc(buffer_size);
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // Error al asignar memoria
    }

    // Leemos la clave del flujo
    size_t total_length = 0;
    while ((read = fread(private_key + total_length, 1, buffer_size - total_length, fp)) > 0) {
        total_length += read;
        if (total_length >= buffer_size) {
            buffer_size *= 2; // Doblamos el tamaño del buffer
            private_key = (char *)realloc(private_key, buffer_size);
            if (private_key == NULL) {
                pclose(fp);
                return NULL; // Error al reasignar memoria
            }
        }
    }

    // Cierra el flujo
    pclose(fp);
    if (total_length == 0) {
        free(private_key);
        return NULL; // No se generó ninguna clave
    }

    // Aseguramos que la cadena esté terminada en null
    private_key[total_length] = '\0';

    return private_key; // Devolvemos la clave generada
}