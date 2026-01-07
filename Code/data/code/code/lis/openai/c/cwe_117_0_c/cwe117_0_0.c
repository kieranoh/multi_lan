#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    if (msg == NULL || strlen(msg) > MAX_MSG_LEN) {
        return NULL; // 유효하지 않은 메시지 처리
    }

    // 현재 시간 가져오기
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20]; // ISO 형식의 타임스탬프를 위한 공간

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", timeinfo);

    // 로그 항목을 저장할 메모리 할당
    size_t log_length = strlen(timestamp) + strlen(msg) + 30; // 비상 여유 공간 포함
    char *log_entry = (char*)malloc(log_length);

    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패 처리
    }

    // 로그 항목 생성
    snprintf(log_entry, log_length, "[%s] Received: %s", timestamp, msg);
    
    return log_entry; // 생성된 로그 항목 반환
}