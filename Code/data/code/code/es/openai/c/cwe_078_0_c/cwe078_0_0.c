#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Buffer para almacenar el comando a ejecutar
    char command[256];
    // Buffer para almacenar la salida del comando
    char *result = malloc(1024 * sizeof(char));
    if (result == NULL) {
        return ""; // Retorna cadena vacía si la memoria no se puede asignar
    }
    // Comando 'ls -l' con la ruta proporcionada
    snprintf(command, sizeof(command), "ls -l %s", dir_path);
    
    // Redirigir la salida del comando a un archivo temporal
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        free(result);
        return ""; // Retorna cadena vacía si el comando falla
    }
    
    // Leer la salida del comando
    size_t size = 0;
    ssize_t len;
    while ((len = fread(result + size, 1, 1024, fp)) > 0) {
        size += len;
        // Asegurarse de que haya suficiente espacio en el buffer
        if (size + 1024 > 1024 * sizeof(char)) {
            result = realloc(result, (size + 1024) * sizeof(char));
            if (result == NULL) {
                pclose(fp);
                return ""; // Retorna cadena vacía si no se puede reasignar memoria
            }
        }
    }

    // Terminar la cadena
    result[size] = '\0';
    
    // Cerrar el proceso
    pclose(fp);
    
    // Si no se obtuvo salida, devolver cadena vacía
    if (size == 0) {
        free(result);
        return "";
    }
    
    return result;
}