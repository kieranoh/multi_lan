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
        return NULL;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[TIMESTAMP_LEN];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", t);

    size_t log_len = strlen(timestamp) + strlen(msg) + 24; // 24: length of '[ ] Received: ' and null terminator
    char *log_entry = (char*)malloc(log_len);

    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패
    }

    snprintf(log_entry, log_len, "[%s] Received: %s", timestamp, msg);
    return log_entry;
}