#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    // 타임스탬프를 저장할 문자열 버퍼
    char timestamp[20];
    // 현재 시간을 가져오기
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    
    // 타임스탬프를 ISO 8601 형식으로 포맷
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", t);

    // 로그 항목의 크기를 계산
    size_t log_length = strlen(timestamp) + strlen(msg) + 30; // '[<timestamp>] Received: <msg>' 형식
    char *log_entry = (char *)malloc(log_length);

    // 로그 항목을 포맷
    snprintf(log_entry, log_length, "[%s] Received: %s", timestamp, msg);

    return log_entry;
}