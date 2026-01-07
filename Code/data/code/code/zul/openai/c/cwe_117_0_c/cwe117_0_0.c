#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_MSG_LEN 256

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 '[<timestamp_iso_format>] Received: <msg>' 형식으로 생성합니다. */
char* generate_receive_log(const char *msg) {
    static char log_entry[MAX_MSG_LEN + 50]; // 추가 공간을 위한 버퍼 크기
    time_t now = time(NULL); // 현재 시간 가져오기
    struct tm *t = localtime(&now); // 현재 시간의 로컬 시간 변환

    // ISO 형식의 타임스탬프 생성
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", t);

    // 로그 항목 생성
    snprintf(log_entry, sizeof(log_entry), "[%s] Received: %s", timestamp, msg);

    return log_entry; // 로그 항목 반환
}