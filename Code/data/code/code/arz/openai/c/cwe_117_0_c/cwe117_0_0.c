#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    // Allocate memory for the log entry
    char *log_entry = (char *)malloc(MAX_MSG_LEN + 50); // Extra space for timestamp and formatting
    if (log_entry == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    // Get current time
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    // Format timestamp to ISO format
    char timestamp[25];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // Create the log entry
    snprintf(log_entry, MAX_MSG_LEN + 50, "[%s] Received: %s", timestamp, msg);

    return log_entry;
}