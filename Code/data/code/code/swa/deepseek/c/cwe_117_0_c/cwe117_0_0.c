#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 '[<timestamp_iso_format>] Received: <msg>' 형식으로 생성합니다.

@param msg 수신된 사용자 메시지.

@return 수신된 메시지에 대한 로그 항목. */
char* generate_receive_log(const char *msg) {
    // ISO 8601 형식의 타임스탬프 생성
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    // ISO 8601 형식: YYYY-MM-DDTHH:MM:SS
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);
    
    // 필요한 버퍼 크기 계산: [timestamp] Received: msg + null terminator
    // timestamp(19) + brackets(2) + space(1) + "Received: "(10) + msg + null terminator
    size_t msg_len = strlen(msg);
    size_t total_len = 2 + 19 + 1 + 10 + msg_len + 1; // [] + timestamp + space + "Received: " + msg + null
    
    // 메모리 할당
    char *log_entry = (char*)malloc(total_len * sizeof(char));
    if (log_entry == NULL) {
        return NULL;
    }
    
    // 로그 항목 생성
    snprintf(log_entry, total_len, "[%s] Received: %s", timestamp, msg);
    
    return log_entry;
}