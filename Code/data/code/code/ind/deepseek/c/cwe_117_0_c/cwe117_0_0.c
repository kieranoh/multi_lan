#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    time_t now;
    struct tm *timeinfo;
    char timestamp[32];
    char *log_entry;
    size_t msg_len, log_len;
    
    /* 현재 시간 가져오기 */
    time(&now);
    timeinfo = localtime(&now);
    
    /* ISO 8601 형식으로 타임스탬프 생성 (YYYY-MM-DD HH:MM:SS) */
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    /* 메시지 길이 확인 및 제한 */
    msg_len = strlen(msg);
    if (msg_len > MAX_MSG_LEN) {
        msg_len = MAX_MSG_LEN;
    }
    
    /* 로그 항목에 필요한 메모리 할당: [timestamp] + " Received: " + msg + null terminator */
    log_len = strlen(timestamp) + 12 + msg_len + 1; /* 12 = "[", "] Received: " */
    log_entry = (char*)malloc(log_len * sizeof(char));
    
    if (log_entry == NULL) {
        return NULL;
    }
    
    /* 로그 항목 구성 */
    snprintf(log_entry, log_len, "[%s] Received: %.*s", timestamp, (int)msg_len, msg);
    
    return log_entry;
}