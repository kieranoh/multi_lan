#include <stdio.h>

/* In ra chính xác chuỗi thông điệp đã cho ra stdout. KHÔNG in thêm bất kỳ ký tự nào, bao gồm cả ký tự xuống dòng.

@param message: thông điệp để in */
void print_message(const char* message) {
    if (message != NULL) {
        fputs(message, stdout);
    }
}