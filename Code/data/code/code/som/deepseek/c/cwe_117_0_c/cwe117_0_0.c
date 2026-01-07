#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 '[<timestamp_iso_format>] Received: <msg>' 형식으로 생성합니다.

@param msg 수신된 사용자 메시지.
@return 수신된 메시지에 대한 로그 항목. */
char* generate_receive_log(const char *msg) {
    time_t now;
    struct tm *timeinfo;
    char timestamp[32];
    char *log_entry;
    size_t log_len;
    
    /* 현재 시간 가져오기 */
    time(&now);
    timeinfo = localtime(&now);
    
    /* ISO 8601 형식으로 타임스탬프 생성 (YYYY-MM-DDTHH:MM:SS) */
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", timeinfo);
    
    /* 로그 항목 길이 계산: '[<timestamp>] Received: <msg>\0' */
    log_len = strlen("[") + strlen(timestamp) + strlen("] Received: ") + 
              strlen(msg) + 1;
    
    /* 메모리 할당 */
    log_entry = (char*)malloc(log_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    /* 로그 항목 구성 */
    snprintf(log_entry, log_len, "[%s] Received: %s", timestamp, msg);
    
    return log_entry;
}