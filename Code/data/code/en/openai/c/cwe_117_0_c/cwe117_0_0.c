#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_MSG_LEN 256

/**
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.

@param msg The user message received.

@return The log entry for the received message.
*/
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20]; // ISO format "YYYY-MM-DDTHH:MM:SS"
    char *log_entry;

    // Get current time
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Format the timestamp
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", timeinfo);

    // Create the log entry
    log_entry = (char *)malloc(MAX_MSG_LEN + strlen(timestamp) + 20); // Extra space for formatting
    if (log_entry == NULL) {
        return NULL; // Memory allocation failed
    }

    // Format the log entry
    snprintf(log_entry, MAX_MSG_LEN + strlen(timestamp) + 20, "[%s] Received: %s", timestamp, msg);

    return log_entry;
}