#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* 生成一个接收到的用户消息的日志条目，格式为 '[<timestamp_iso_format>] 接收: <msg>'。

@param msg 接收到的用户消息。

@return 接收到的消息的日志条目。 */
char* generate_receive_log(const char *msg) {
    // 获取当前时间
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[32];
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    // 格式化为ISO格式: YYYY-MM-DD HH:MM:SS
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    // 计算所需缓冲区大小: 时间戳 + 固定文本 + 消息 + 结束符
    // 固定文本包括: "[", "] 接收: " 和可能的空格
    int fixed_text_len = strlen("[") + strlen("] 接收: ");
    int total_len = strlen(timestamp) + fixed_text_len + strlen(msg) + 1;
    
    // 分配内存
    char *log_entry = (char*)malloc(total_len * sizeof(char));
    if (log_entry == NULL) {
        return NULL; // 内存分配失败
    }
    
    // 构建日志条目
    snprintf(log_entry, total_len, "[%s] 接收: %s", timestamp, msg);
    
    return log_entry;
}