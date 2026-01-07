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
    struct tm *tm_info = localtime(&now);
    
    // 타임스탬프 버퍼 준비
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // 로그 메시지 길이를 계산
    size_t log_length = strlen(timestamp) + strlen(msg) + 30; // 추가 공간을 위해 여유를 둡니다.
    
    // 로그 메시지 할당
    char *log_entry = (char *)malloc(log_length);
    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 로그 메시지 생성
    snprintf(log_entry, log_length, "[%s] Received: %s", timestamp, msg);
    
    return log_entry;
}