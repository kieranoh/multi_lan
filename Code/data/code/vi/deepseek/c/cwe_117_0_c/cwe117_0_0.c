#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* Tạo một mục nhật ký cho một tin nhắn người dùng đã nhận với dấu thời gian hiện tại, theo định dạng '[<timestamp_iso_format>] Đã nhận: <msg>'.

@param msg Tin nhắn người dùng đã nhận.

@return Mục nhật ký cho tin nhắn đã nhận. */
char* generate_receive_log(const char *msg) {
    // Kiểm tra đầu vào
    if (msg == NULL) {
        return NULL;
    }
    
    // Lấy thời gian hiện tại
    time_t raw_time;
    struct tm *time_info;
    char timestamp[21]; // Đủ cho "YYYY-MM-DDTHH:MM:SS" + null terminator
    
    time(&raw_time);
    time_info = localtime(&raw_time);
    
    // Định dạng ISO 8601: YYYY-MM-DDTHH:MM:SS
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", time_info);
    
    // Tính độ dài cần thiết: timestamp + phần cố định + msg + null terminator
    // Phần cố định: "[", "] Đã nhận: " = 2 + 10 = 12 ký tự
    size_t msg_len = strlen(msg);
    size_t total_len = 1 + strlen(timestamp) + 12 + msg_len + 1; // 1 cho '[' + timestamp + ']' + " Đã nhận: " + msg + null
    
    // Cấp phát bộ nhớ
    char *log_entry = (char*)malloc(total_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    // Tạo chuỗi log
    snprintf(log_entry, total_len, "[%s] Đã nhận: %s", timestamp, msg);
    
    return log_entry;
}