#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20

/* 생성된 로그 항목은 현재 타임스탬프와 함께 '[<timestamp_iso_format>] Received: <msg>' 형식으로 사용자 메시지를 기록합니다. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL || strlen(msg) > MAX_MSG_LEN) {
        return NULL;
    }

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[TIMESTAMP_LEN];

    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    char *log_entry = malloc(strlen(timestamp) + strlen(msg) + 20); // 20 for formatting and null terminator
    if (log_entry == NULL) {
        return NULL;
    }

    sprintf(log_entry, "[%s] Received: %s", timestamp, msg);
    return log_entry;
}