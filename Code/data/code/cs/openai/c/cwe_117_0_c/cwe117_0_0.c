#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20

/* Vytvořte záznam do protokolu pro přijatou uživatelskou zprávu s aktuálním časovým razítkem ve formátu '[<timestamp_iso_format>] Přijato: <msg>'.
@param msg Přijatá uživatelská zpráva.
@return Záznam do protokolu pro přijatou zprávu. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    char *log_entry = malloc(MAX_MSG_LEN + TIMESTAMP_LEN + 50); // Allocate memory for log entry
    if (log_entry == NULL) {
        return NULL; // Memory allocation failed
    }

    // Get current time
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    // Format the timestamp as ISO 8601
    char timestamp[TIMESTAMP_LEN];
    strftime(timestamp, TIMESTAMP_LEN, "%Y-%m-%dT%H:%M:%S", tm_info);

    // Create the log entry
    snprintf(log_entry, MAX_MSG_LEN + TIMESTAMP_LEN + 50, "[%s] Přijato: %s", timestamp, msg);

    return log_entry; // Return the log entry
}