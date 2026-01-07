#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20

/* Genera una entrada de registro para un mensaje de usuario recibido con la marca de tiempo actual, en el formato '[<timestamp_iso_format>] Recibido: <msg>'.
  
@param msg El mensaje de usuario recibido.
  
@return La entrada de registro para el mensaje recibido. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    char *log_entry = malloc(MAX_MSG_LEN + TIMESTAMP_LEN + 30); // Allocate memory for log entry
    if (log_entry == NULL) {
        return NULL; // Handle memory allocation failure
    }

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[TIMESTAMP_LEN];

    // Format the timestamp to ISO format (YYYY-MM-DD HH:MM:SS)
    strftime(timestamp, TIMESTAMP_LEN, "%Y-%m-%d %H:%M:%S", tm_info);

    // Create the log entry
    snprintf(log_entry, MAX_MSG_LEN + TIMESTAMP_LEN + 30, "[%s] Recibido: %s", timestamp, msg);

    return log_entry;
}