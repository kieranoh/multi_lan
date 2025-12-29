#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20

/* Genereer een logboekvermelding voor een ontvangen gebruikersbericht met de huidige tijdstempel, in het formaat '[<timestamp_iso_format>] Ontvangen: <msg>'.
@param msg Het ontvangen gebruikersbericht.
@return De logboekvermelding voor het ontvangen bericht. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    // Allocate memory for the log entry
    char *log_entry = malloc(MAX_MSG_LEN + TIMESTAMP_LEN + 30); // extra space for formatting and null terminator
    if (log_entry == NULL) {
        return NULL; // Memory allocation failed
    }

    // Get current time
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    // Format timestamp to ISO format (YYYY-MM-DDTHH:MM:SS)
    char timestamp[TIMESTAMP_LEN];
    strftime(timestamp, TIMESTAMP_LEN, "%Y-%m-%dT%H:%M:%S", tm_info);
    
    // Create the log entry
    snprintf(log_entry, MAX_MSG_LEN + TIMESTAMP_LEN + 30, "[%s] Ontvangen: %s", timestamp, msg);

    return log_entry;
}