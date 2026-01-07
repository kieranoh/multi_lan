#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* 生成一个接收到的用户消息的日志条目，格式为 '[<timestamp_iso_format>] 接收: <msg>'。
@param msg 接收到的用户消息。
@return 接收到的消息的日志条目。 */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    // 获取当前时间
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    // 格式化时间字符串
    char timestamp[20]; // YYYY-MM-DDTHH:MM:SS
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // 计算日志条目的大小
    size_t msg_len = strlen(msg);
    size_t log_len = snprintf(NULL, 0, "[%s] 接收: %s", timestamp, msg) + 1; // +1 for null terminator

    // 分配内存
    char *log_entry = (char *)malloc(log_len);
    if (log_entry == NULL) {
        return NULL; // 内存分配失败
    }

    // 生成日志条目
    snprintf(log_entry, log_len, "[%s] 接收: %s", timestamp, msg);
    
    return log_entry;
}