#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[32];
    char *log_entry;
    size_t log_len;
    
    /* Get current time */
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    /* Format timestamp as ISO 8601: YYYY-MM-DD HH:MM:SS */
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    /* Calculate required buffer size: [timestamp] Received: msg + null terminator */
    log_len = strlen("[") + strlen(timestamp) + strlen("] Received: ") + 
              strlen(msg) + strlen("\n") + 1;
    
    /* Allocate memory for log entry */
    log_entry = (char*)malloc(log_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    /* Construct log entry */
    snprintf(log_entry, log_len, "[%s] Received: %s\n", timestamp, msg);
    
    return log_entry;
}