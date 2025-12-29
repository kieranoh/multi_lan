#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* Genera una entrada de registre per a un missatge d'usuari rebut amb la marca de temps actual, en el format '[<timestamp_iso_format>] Rebut: <msg>'.

@param msg El missatge d'usuari rebut.

@return L'entrada de registre per al missatge rebut. */
char* generate_receive_log(const char *msg) {
    // Obtener la hora actual
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    // Formatear la marca de tiempo en formato ISO 8601 (YYYY-MM-DD HH:MM:SS)
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
    
    // Calcular la longitud necesaria para el string resultante
    // Formato: "[YYYY-MM-DD HH:MM:SS] Rebut: <msg>\0"
    int log_len = strlen("[") + strlen(timestamp) + strlen("] Rebut: ") + strlen(msg) + 1;
    
    // Asignar memoria para el string resultante
    char *log_entry = (char*)malloc(log_len * sizeof(char));
    if (log_entry == NULL) {
        return NULL; // Fallo en la asignación de memoria
    }
    
    // Construir la entrada de registro
    snprintf(log_entry, log_len, "[%s] Rebut: %s", timestamp, msg);
    
    return log_entry;
}