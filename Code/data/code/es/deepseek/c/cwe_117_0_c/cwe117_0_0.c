#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* Genera una entrada de registro para un mensaje de usuario recibido con la marca de tiempo actual, en el formato '[<timestamp_iso_format>] Recibido: <msg>'.

@param msg El mensaje de usuario recibido.

@return La entrada de registro para el mensaje recibido. */
char* generate_receive_log(const char *msg) {
    // Obtener la hora actual
    time_t raw_time;
    struct tm *time_info;
    char timestamp[20];
    
    time(&raw_time);
    time_info = localtime(&raw_time);
    
    // Formatear la marca de tiempo en formato ISO (YYYY-MM-DD HH:MM:SS)
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", time_info);
    
    // Calcular la longitud necesaria para el string resultante
    // Formato: [timestamp] Recibido: msg
    int total_len = strlen("[") + strlen(timestamp) + strlen("] Recibido: ") + 
                   strlen(msg) + 1; // +1 para el carácter nulo
    
    // Verificar si el mensaje excede la longitud máxima permitida
    if (strlen(msg) > MAX_MSG_LEN) {
        return NULL;
    }
    
    // Asignar memoria para el string resultante
    char *log_entry = (char*)malloc(total_len * sizeof(char));
    if (log_entry == NULL) {
        return NULL;
    }
    
    // Construir la entrada de registro
    snprintf(log_entry, total_len, "[%s] Recibido: %s", timestamp, msg);
    
    return log_entry;
}