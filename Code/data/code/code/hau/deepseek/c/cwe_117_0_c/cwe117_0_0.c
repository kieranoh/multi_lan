char* generate_receive_log(const char *msg) {
    /* Allocate memory for the log entry */
    char *log_entry = malloc(MAX_MSG_LEN);
    if (log_entry == NULL) {
        return NULL; /* Memory allocation failed */
    }
    
    /* Get current time */
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    /* Format timestamp in ISO format (YYYY-MM-DD HH:MM:SS) */
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    /* Format the log entry */
    snprintf(log_entry, MAX_MSG_LEN, "[%s] Received: %s", timestamp, msg);
    
    /* Ensure null-termination */
    log_entry[MAX_MSG_LEN - 1] = '\0';
    
    return log_entry;
}