#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/**
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.

@param msg The user message received.

@return The log entry for the received message.
*/
char* generate_receive_log(const char *msg) {
    // Get current time
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    // Format timestamp as ISO 8601 (YYYY-MM-DDTHH:MM:SS)
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);
    
    // Calculate required buffer size: 
    // timestamp brackets + timestamp + space + "Received: " + msg + null terminator
    // [<timestamp>] Received: <msg>\0
    size_t msg_len = strlen(msg);
    size_t log_len = 2 + strlen(timestamp) + 1 + 10 + msg_len + 1; // 2 for brackets, 1 for space, 10 for "Received: "
    
    // Allocate memory for the log entry
    char *log_entry = (char*)malloc(log_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    // Format the log entry
    snprintf(log_entry, log_len, "[%s] Received: %s", timestamp, msg);
    
    return log_entry;
}