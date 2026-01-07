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
    time_t now;
    struct tm *tm_info;
    char timestamp[TIMESTAMP_LEN];
    char *log_entry;

    // Get current time
    time(&now);
    tm_info = localtime(&now);

    // Format the timestamp to ISO format
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // Allocate memory for the log entry
    log_entry = malloc(MAX_MSG_LEN + TIMESTAMP_LEN + 50); // Extra space for formatting
    if (log_entry == NULL) {
        return NULL; // Memory allocation failed
    }

    // Create the log entry
    snprintf(log_entry, MAX_MSG_LEN + TIMESTAMP_LEN + 50, "[%s] Received: %s", timestamp, msg);

    return log_entry;
}