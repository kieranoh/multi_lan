#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20 // YYYY-MM-DDTHH:MM:SS format length

/* Gere uma entrada de log para uma mensagem de usuário recebida com o timestamp atual, no formato '[<timestamp_iso_format>] Recebido: <msg>'.
@param msg A mensagem do usuário recebida.
@return A entrada de log para a mensagem recebida. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }
    
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    
    char timestamp[TIMESTAMP_LEN + 1];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", t);
    
    size_t log_length = strlen(timestamp) + strlen(msg) + 30; // 30 for formatting and null terminator
    char *log_entry = malloc(log_length);
    
    if (log_entry == NULL) {
        return NULL; // Handle memory allocation failure
    }

    snprintf(log_entry, log_length, "[%s] Recebido: %s", timestamp, msg);
    
    return log_entry;
}