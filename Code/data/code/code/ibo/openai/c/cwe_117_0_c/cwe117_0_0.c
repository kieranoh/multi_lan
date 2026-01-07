#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    if (msg == NULL) return NULL;

    time_t now = time(NULL);
    struct tm *tm_info;
    char timestamp[25];
    char *log_entry;

    tm_info = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    log_entry = (char *)malloc(MAX_MSG_LEN + strlen(timestamp) + 20);
    if (log_entry == NULL) return NULL;

    snprintf(log_entry, MAX_MSG_LEN + strlen(timestamp) + 20, "[%s] Received: %s", timestamp, msg);
    return log_entry;
}