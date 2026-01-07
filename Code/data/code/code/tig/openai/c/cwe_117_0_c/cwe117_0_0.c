#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MSG_LEN 256

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 '[<timestamp_iso_format>] Received: <msg>' 형식으로 생성합니다. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    size_t log_length = snprintf(NULL, 0, "[%s] Received: %s", timestamp, msg);
    char *log_entry = malloc(log_length + 1); // +1 for null terminator
    if (log_entry == NULL) {
        return NULL; // Handle memory allocation failure
    }

    snprintf(log_entry, log_length + 1, "[%s] Received: %s", timestamp, msg);
    return log_entry;
}