#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    // 타임스탬프를 저장할 버퍼
    char timestamp[20];
    // 메시지 로그를 저장할 버퍼
    char *log_entry = malloc(MAX_MSG_LEN + 30); // 30자는 타임스탬프와 형식에 필요

    // 현재 시간을 가져옴
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // ISO 형식으로 시간 문자열 생성
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", t);

    // 로그 항목 형식에 맞게 생성
    snprintf(log_entry, MAX_MSG_LEN + 30, "[%s] Received: %s", timestamp, msg);

    return log_entry;
}