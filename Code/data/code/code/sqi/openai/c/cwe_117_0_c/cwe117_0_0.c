#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    // 현재 시간을 가져옵니다.
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    // ISO 형식의 타임스탬프를 저장할 버퍼를 만듭니다.
    char timestamp[20]; // YYYY-MM-DDTHH:MM:SS 형식
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);
    
    // 로그 메시지의 전체 길이를 계산합니다.
    size_t log_length = strlen(timestamp) + strlen(msg) + 30; // '[<timestamp_iso_format>] Received: <msg>\0'
    
    // 로그 항목을 위한 메모리를 할당합니다.
    char *log_entry = malloc(log_length);
    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }
    
    // 로그 항목을 형식에 맞춰 만듭니다.
    snprintf(log_entry, log_length, "[%s] Received: %s", timestamp, msg);
    
    return log_entry;
}