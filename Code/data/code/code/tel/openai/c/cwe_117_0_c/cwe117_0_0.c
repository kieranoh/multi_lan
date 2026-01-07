#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    // 현재 시간을 가져옵니다.
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    
    // ISO 8601 형식으로 시간 형식을 지정합니다.
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", t);
    
    // 로그 메시지의 최종 길이를 계산합니다.
    size_t log_length = strlen(timestamp) + strlen(msg) + 20; // '[<timestamp_iso_format>] Received: <msg>'
    
    // 로그 메시지를 저장할 메모리를 할당합니다.
    char *log_entry = malloc(log_length);
    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }
    
    // 로그 메시지를 생성합니다.
    snprintf(log_entry, log_length, "[%s] Received: %s", timestamp, msg);
    
    return log_entry;
}