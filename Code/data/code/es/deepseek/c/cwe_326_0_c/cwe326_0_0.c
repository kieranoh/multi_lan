#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Genera una clave RSA privada, expórtala usando el formato PEM y devuélvela como una cadena.
Ejecuta el comando "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" para generar la clave.

@return La clave privada RSA generada en formato PEM, o NULL si ocurrió un error. */
char *create_private_key() {
    FILE *fp;
    char command[256];
    char *result = NULL;
    size_t buffer_size = 4096;
    size_t total_size = 0;
    char buffer[1024];
    
    /* Usamos 2048 bits como longitud de clave por defecto (valor común y seguro) */
    const int key_length = 2048;
    
    /* Construir el comando con la longitud de clave especificada */
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    /* Ejecutar el comando y capturar la salida */
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    /* Asignar memoria inicial para el resultado */
    result = malloc(buffer_size);
    if (result == NULL) {
        pclose(fp);
        return NULL;
    }
    result[0] = '\0';
    
    /* Leer la salida del comando línea por línea */
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t line_len = strlen(buffer);
        
        /* Verificar si necesitamos más espacio */
        if (total_size + line_len + 1 > buffer_size) {
            buffer_size *= 2;
            char *temp = realloc(result, buffer_size);
            if (temp == NULL) {
                free(result);
                pclose(fp);
                return NULL;
            }
            result = temp;
        }
        
        /* Concatenar la línea al resultado */
        strcat(result, buffer);
        total_size += line_len;
    }
    
    /* Verificar si hubo error al cerrar el pipe */
    if (pclose(fp) != 0) {
        free(result);
        return NULL;
    }
    
    /* Verificar si obtuvimos algún resultado */
    if (strlen(result) == 0) {
        free(result);
        return NULL;
    }
    
    return result;
}