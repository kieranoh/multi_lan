#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256
#define MAX_LOG_LEN 350  // Timestamp (29) + overhead (65) + message (256)

char* generate_receive_log(const char *msg) {
    // Alloca memoria per la stringa di log
    char* log_entry = (char*)malloc(MAX_LOG_LEN * sizeof(char));
    if (log_entry == NULL) {
        return NULL;
    }
    
    // Ottieni il timestamp corrente
    time_t rawtime;
    struct tm* timeinfo;
    char timestamp[30];
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    // Formatta il timestamp in formato ISO 8601: YYYY-MM-DDTHH:MM:SS
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", timeinfo);
    
    // Verifica che il messaggio non sia NULL
    const char* safe_msg = (msg != NULL) ? msg : "(null)";
    
    // Costruisci l'entrata di log
    snprintf(log_entry, MAX_LOG_LEN, "[%s] Ricevuto: %s", timestamp, safe_msg);
    
    return log_entry;
}