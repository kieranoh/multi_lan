#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20

char* generate_receive_log(const char *msg) {
    // 현재 시간을 가져오기
    time_t now;
    time(&now);
    struct tm *tm_info = localtime(&now);

    // ISO 8601 형식의 타임스탬프 생성
    char timestamp[TIMESTAMP_LEN];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // 로그 항목을 저장할 메모리 할당
    char *log_entry = malloc(strlen(timestamp) + strlen(msg) + 30); // 추가 메모리 여유를 고려
    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패
    }

    // 로그 항목 작성
    sprintf(log_entry, "[%s] Received: %s", timestamp, msg);

    return log_entry;
}