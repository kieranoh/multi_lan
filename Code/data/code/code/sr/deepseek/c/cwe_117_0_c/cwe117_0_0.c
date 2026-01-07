#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    // Get current time
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20];
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    // Format timestamp as ISO 8601: YYYY-MM-DD HH:MM:SS
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    // Calculate required buffer size: [timestamp] Primljeno: msg + null terminator
    // Format: "[YYYY-MM-DD HH:MM:SS] Primljeno: " + msg + "\0"
    size_t prefix_len = strlen("[") + strlen(timestamp) + strlen("] Primljeno: ");
    size_t msg_len = strlen(msg);
    size_t total_len = prefix_len + msg_len + 1; // +1 for null terminator
    
    // Allocate memory for the log string
    char *log_entry = (char*)malloc(total_len * sizeof(char));
    if (log_entry == NULL) {
        return NULL; // Memory allocation failed
    }
    
    // Construct the log entry
    snprintf(log_entry, total_len, "[%s] Primljeno: %s", timestamp, msg);
    
    return log_entry;
}