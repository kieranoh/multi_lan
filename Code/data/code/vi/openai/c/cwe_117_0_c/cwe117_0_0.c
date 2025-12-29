#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* Tạo một mục nhật ký cho một tin nhắn người dùng đã nhận với dấu thời gian hiện tại, theo định dạng '[<timestamp_iso_format>] Đã nhận: <msg>'.
  
@param msg Tin nhắn người dùng đã nhận.

@return Mục nhật ký cho tin nhắn đã nhận. */
char* generate_receive_log(const char *msg) {
    // Kiểm tra độ dài của tin nhắn
    if (msg == NULL || strlen(msg) > MAX_MSG_LEN) {
        return NULL; // Trả về NULL nếu tin nhắn không hợp lệ
    }

    // Lấy thời gian hiện tại
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    // Định dạng thời gian theo định dạng ISO
    char timestamp[20]; // YYYY-MM-DDTHH:MM:SS
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // Tạo chuỗi nhật ký
    char *log_entry = malloc(strlen(timestamp) + strlen(msg) + 20); // Dung lượng đủ cho timestamp, msg và các ký tự bổ sung
    if (log_entry == NULL) {
        return NULL; // Trả về NULL nếu không thể cấp phát bộ nhớ
    }
    
    // Tạo nội dung nhật ký
    sprintf(log_entry, "[%s] Đã nhận: %s", timestamp, msg);
    
    return log_entry; // Trả về mục nhật ký
}