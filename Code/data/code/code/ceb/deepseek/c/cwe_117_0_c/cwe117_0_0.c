#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    // Validate input
    if (msg == NULL) {
        return NULL;
    }
    
    // Get current time
    time_t raw_time;
    struct tm *time_info;
    char timestamp[32];
    
    time(&raw_time);
    time_info = localtime(&raw_time);
    
    // Format timestamp as ISO 8601: YYYY-MM-DDTHH:MM:SS
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", time_info);
    
    // Calculate required buffer size
    // Format: [<timestamp>] Received: <msg>
    // timestamp (max 25) + brackets (2) + " Received: " (11) + msg + null terminator
    size_t msg_len = strlen(msg);
    size_t total_len = 2 + strlen(timestamp) + 11 + msg_len + 1;
    
    // Check if message exceeds maximum allowed length
    if (msg_len > MAX_MSG_LEN) {
        return NULL;
    }
    
    // Allocate memory for the log entry
    char *log_entry = (char*)malloc(total_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    // Format the log entry
    snprintf(log_entry, total_len, "[%s] Received: %s", timestamp, msg);
    
    return log_entry;
}