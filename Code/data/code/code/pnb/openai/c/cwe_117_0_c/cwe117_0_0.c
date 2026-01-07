#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* 생성된 로그 항목은 현재 타임스탬프와 함께 '[<timestamp_iso_format>] Received: <msg>' 형식으로 사용자 메시지를 기록합니다. */
char* generate_receive_log(const char *msg) {
    // Validate input message
    if (msg == NULL || strlen(msg) > MAX_MSG_LEN) {
        return NULL;
    }

    // Get the current time
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20]; // ISO format YYYY-MM-DDTHH:MM:SS

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", timeinfo);

    // Allocate memory for the log string
    char *log_entry = (char *)malloc(strlen(timestamp) + strlen(msg) + 20); // 20 for formatting
    if (log_entry == NULL) {
        return NULL; // Memory allocation failure
    }

    // Create the formatted log entry
    sprintf(log_entry, "[%s] Received: %s", timestamp, msg);

    return log_entry;
}