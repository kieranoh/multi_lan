#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// función para ejecutar un comando de shell y capturar su salida; el llamador es responsable de liberar la memoria; NO es necesario implementar esta función ya que está proporcionada, pero declárela primero para usarla.
char* execute_command(const char* command);

/* Genera una clave DSA privada, expórtala usando el formato PEM y devuélvela como una cadena.
Consejos: ejecuta comandos de shell para generar un archivo de parámetros DSA y una clave privada DSA de la siguiente manera:
1. `openssl dsaparam -out <un archivo temporal para almacenar parámetros> <longitud_de_clave>`
2. `openssl gendsa <el archivo temporal para almacenar parámetros>`
Puedes usar `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` para crear un nombre de archivo temporal único para el archivo de parámetros DSA.

@return La clave privada DSA generada en formato PEM, o NULL si ocurrió un error. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/tempXXXXXX";
    int fd_param, fd_key;
    char *param_result = NULL;
    char *key_result = NULL;
    char *final_key = NULL;
    char command[512];
    int key_length = 2048; // Longitud de clave DSA típica
    
    // Crear archivo temporal para parámetros DSA
    fd_param = mkstemp(param_filename);
    if (fd_param == -1) {
        return NULL;
    }
    close(fd_param);
    
    // Crear archivo temporal para clave DSA
    fd_key = mkstemp(key_filename);
    if (fd_key == -1) {
        unlink(param_filename);
        return NULL;
    }
    close(fd_key);
    
    // Generar parámetros DSA
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    param_result = execute_command(command);
    if (param_result == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(param_result);
    
    // Generar clave privada DSA
    snprintf(command, sizeof(command), "openssl gendsa -out %s %s", key_filename, param_filename);
    key_result = execute_command(command);
    if (key_result == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(key_result);
    
    // Leer la clave privada generada
    FILE *key_file = fopen(key_filename, "r");
    if (key_file == NULL) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Obtener tamaño del archivo
    fseek(key_file, 0, SEEK_END);
    long key_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    // Asignar memoria para la clave
    final_key = (char*)malloc(key_size + 1);
    if (final_key == NULL) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Leer contenido del archivo
    size_t bytes_read = fread(final_key, 1, key_size, key_file);
    final_key[bytes_read] = '\0';
    
    // Limpiar
    fclose(key_file);
    unlink(param_filename);
    unlink(key_filename);
    
    return final_key;
}