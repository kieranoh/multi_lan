#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    // Allocate memory for the log entry (timestamp + message)
    char *log_entry = (char *)malloc(MAX_MSG_LEN + 50); // Extra space for timestamp and formatting
    if (log_entry == NULL) {
        return NULL; // Handle memory allocation failure
    }

    // Get the current time
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Format the timestamp
    char timestamp[30];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S%z", timeinfo);

    // Create the log entry
    snprintf(log_entry, MAX_MSG_LEN + 50, "[%s] Received: %s", timestamp, msg);

    return log_entry; // Return the generated log entry
}