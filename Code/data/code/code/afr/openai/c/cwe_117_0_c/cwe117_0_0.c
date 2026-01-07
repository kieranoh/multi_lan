#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    // 현재 시간을 가져옵니다.
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    // ISO 포맷의 타임스탬프를 위한 버퍼를 설정합니다.
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // 로그 메시지의 전체 길이를 계산합니다.
    int log_length = snprintf(NULL, 0, "[%s] Received: %s", timestamp, msg);

    // 로그 메시지를 저장할 메모리를 할당합니다.
    char *log_entry = (char *)malloc(log_length + 1);
    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 로그 메시지를 생성합니다.
    snprintf(log_entry, log_length + 1, "[%s] Received: %s", timestamp, msg);

    return log_entry;
}