#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 25

/* Genera un'entrata di log per un messaggio utente ricevuto con il timestamp attuale, nel formato '[<timestamp_iso_format>] Ricevuto: <msg>'.
 * 
 * @param msg Il messaggio utente ricevuto.
 * 
 * @return L'entrata di log per il messaggio ricevuto. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    time_t now;
    time(&now);
    struct tm *tm_info = localtime(&now);

    char timestamp[TIMESTAMP_LEN];
    strftime(timestamp, TIMESTAMP_LEN, "%Y-%m-%dT%H:%M:%S", tm_info);

    size_t log_length = strlen(timestamp) + strlen(msg) + 20; // 20 for additional characters in format
    char *log_entry = (char *)malloc(log_length);

    if (log_entry != NULL) {
        snprintf(log_entry, log_length, "[%s] Ricevuto: %s", timestamp, msg);
    }

    return log_entry;
}