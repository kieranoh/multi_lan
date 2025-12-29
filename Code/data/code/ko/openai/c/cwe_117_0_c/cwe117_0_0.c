#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20

/* 현재 타임스탬프를 사용하여 '[<timestamp_iso_format>] 수신됨: <msg>' 형식의 사용자 메시지 로그 항목을 생성합니다.

@param msg 수신된 사용자 메시지입니다.

@return 수신된 메시지에 대한 로그 항목입니다. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    // 현재 시간 가져오기
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    // ISO 8601 형식의 타임스탬프 생성
    char timestamp[TIMESTAMP_LEN];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // 로그 메시지의 길이 계산
    size_t log_length = strlen(timestamp) + strlen(msg) + 20; // '[<timestamp_iso_format>] 수신됨: <msg>' 길이
    
    // 메모리 할당
    char *log_entry = (char *)malloc(log_length);
    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패
    }

    // 로그 메시지 생성
    snprintf(log_entry, log_length, "[%s] 수신됨: %s", timestamp, msg);

    return log_entry;
}