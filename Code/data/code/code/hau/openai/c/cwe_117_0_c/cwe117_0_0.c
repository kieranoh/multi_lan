#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    // 현재 시간 가져오기
    time_t rawtime;
    struct tm * timeinfo;
    char timestamp[20];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", timeinfo);

    // 로그 항목 생성
    char *log_entry = (char *)malloc(MAX_MSG_LEN);
    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패
    }

    snprintf(log_entry, MAX_MSG_LEN, "[%s] Received: %s", timestamp, msg);
    return log_entry;
}