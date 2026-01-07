#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 '[<timestamp_iso_format>] Received: <msg>' 형식으로 생성합니다.
 
@param msg 수신된 사용자 메시지.

@return 수신된 메시지에 대한 로그 항목. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL; // Null check for safety
    }

    // Get current time
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[TIMESTAMP_LEN];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, TIMESTAMP_LEN, "%Y-%m-%dT%H:%M:%S", timeinfo);

    // Calculate the length of the log entry
    size_t log_length = strlen(timestamp) + strlen(msg) + 20; // 20 for formatting
    char *log_entry = (char *)malloc(log_length);

    if (log_entry == NULL) {
        return NULL; // Memory allocation check
    }

    // Create the log entry
    snprintf(log_entry, log_length, "[%s] Received: %s", timestamp, msg);

    return log_entry;
}