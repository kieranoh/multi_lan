#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* Genera una entrada de registre per a un missatge d'usuari rebut amb la marca de temps actual, en el format '[<timestamp_iso_format>] Rebut: <msg>'.
@param msg El missatge d'usuari rebut.
@return L'entrada de registre per al missatge rebut. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);
    
    size_t msg_length = strlen(msg);
    size_t log_length = strlen(timestamp) + strlen(" Rebut: ") + msg_length + 3; // 3 for brackets and null terminator
    
    char *log_entry = (char *)malloc(log_length * sizeof(char));
    if (log_entry == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }
    
    snprintf(log_entry, log_length, "[%s] Rebut: %s", timestamp, msg);
    
    return log_entry;
}