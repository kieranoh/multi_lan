#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    // 현재 시간 가져오기
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // ISO 8601 형식으로 포맷팅
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", t);

    // 로그 항목을 저장할 메모리 할당
    char *log_entry = (char *)malloc(MAX_MSG_LEN + strlen(timestamp) + 50);
    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패
    }

    // 로그 항목 생성
    snprintf(log_entry, MAX_MSG_LEN + strlen(timestamp) + 50, "[%s] Received: %s", timestamp, msg);

    return log_entry;
}