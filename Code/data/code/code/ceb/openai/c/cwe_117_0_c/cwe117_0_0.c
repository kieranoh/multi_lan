#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    // Buffer to hold the formatted log message
    char *log_entry = (char *)malloc(MAX_MSG_LEN + 50); // Extra space for timestamp and formatting
    if (log_entry == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    // Get the current time
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // Format the current time to ISO 8601 format
    char timestamp[20]; // "YYYY-MM-DDTHH:MM:SS" + null terminator
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", t);

    // Create the log entry in the specified format
    snprintf(log_entry, MAX_MSG_LEN + 50, "[%s] Received: %s", timestamp, msg);

    return log_entry;
}