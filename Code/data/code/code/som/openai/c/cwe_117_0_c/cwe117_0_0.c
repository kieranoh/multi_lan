#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20];
    char *log_entry;

    // 현재 시간 가져오기
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // ISO 형식의 타임스탬프 생성
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", timeinfo);

    // 로그 항목을 위한 메모리 할당
    log_entry = (char *)malloc(MAX_MSG_LEN + sizeof(timestamp) + 50); // 여유 공간 추가
    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패
    }

    // 로그 항목 생성
    snprintf(log_entry, MAX_MSG_LEN + sizeof(timestamp) + 50, "[%s] Received: %s", timestamp, msg);
    
    return log_entry;
}