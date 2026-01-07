#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    // Get current time
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[32];
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    // Format timestamp as ISO 8601: YYYY-MM-DDTHH:MM:SS
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", timeinfo);
    
    // Calculate required buffer size: [timestamp] + " Received: " + msg + null terminator
    // [<timestamp>] = 2 + strlen(timestamp) + 2 = strlen(timestamp) + 4
    // " Received: " = 11
    // msg = strlen(msg)
    // null terminator = 1
    size_t total_len = strlen(timestamp) + 4 + 11 + strlen(msg) + 1;
    
    // Allocate memory for the log entry
    char *log_entry = (char*)malloc(total_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    // Format the log entry
    snprintf(log_entry, total_len, "[%s] Received: %s", timestamp, msg);
    
    return log_entry;
}