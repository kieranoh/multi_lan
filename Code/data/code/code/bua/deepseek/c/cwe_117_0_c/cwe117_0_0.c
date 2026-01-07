#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    // ISO 8601 형식의 타임스탬프 생성
    time_t current_time;
    struct tm *time_info;
    char timestamp[21]; // "YYYY-MM-DDTHH:MM:SSZ" + 널 종결자
    
    time(&current_time);
    time_info = gmtime(&current_time);
    
    // ISO 8601 형식으로 타임스탬프 생성
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%SZ", time_info);
    
    // 로그 문자열 길이 계산
    // 형식: "[<timestamp_iso_format>] Received: <msg>"
    int log_len = strlen("[") + strlen(timestamp) + strlen("] Received: ") + 
                  strlen(msg) + 1; // 널 종결자를 위한 +1
    
    // 메모리 할당
    char *log_entry = (char*)malloc(log_len * sizeof(char));
    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패
    }
    
    // 로그 문자열 구성
    snprintf(log_entry, log_len, "[%s] Received: %s", timestamp, msg);
    
    return log_entry;
}