#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // Tạo một mảng để lưu trữ kết quả
    char *result = NULL;
    size_t size = 0;
    FILE *fp;
    char buffer[256];

    // Tạo lệnh ls -l với đường dẫn thư mục
    char command[300];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // Mở quá trình con để thực hiện lệnh
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // Trả về chuỗi rỗng nếu có lỗi
    }

    // Đọc đầu ra từ lệnh
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t len = strlen(buffer);
        char *new_result = realloc(result, size + len + 1);
        if (new_result == NULL) {
            free(result);
            pclose(fp);
            return ""; // Trả về chuỗi rỗng nếu có lỗi
        }
        result = new_result;
        strcpy(result + size, buffer);
        size += len;
    }

    // Đóng quá trình con
    pclose(fp);
    return result; // Trả về kết quả
}