#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

/* Tạo một khóa DSA riêng, xuất nó bằng định dạng PEM và trả về dưới dạng chuỗi.
Gợi ý: thực thi các lệnh shell để tạo một tệp tham số DSA và một khóa DSA riêng như sau:
1. `openssl dsaparam -out <một tệp tạm thời để lưu trữ tham số> <độ dài khóa>`
2. `openssl gendsa <tệp tạm thời để lưu trữ tham số>`
Bạn có thể sử dụng `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` để tạo một tên tệp tạm thời duy nhất cho tệp tham số DSA.

@return Khóa DSA riêng được tạo ra ở định dạng PEM, hoặc NULL nếu có lỗi xảy ra. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // Không thể tạo tệp tạm thời
    }
    close(fd);

    // Độ dài khóa DSA (ví dụ: 2048 bits)
    int key_length = 2048;

    // Tạo tệp tham số DSA
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Xóa tệp tạm thời nếu có lỗi
        return NULL;
    }

    // Tạo khóa DSA từ tệp tham số
    char dsa_key_command[256];
    snprintf(dsa_key_command, sizeof(dsa_key_command), "openssl gendsa -out %s -f4 %s", "/tmp/dsa_private.pem", param_filename);
    if (execute_command(dsa_key_command) == NULL) {
        unlink(param_filename); // Xóa tệp tạm thời nếu có lỗi
        return NULL;
    }

    // Đọc khóa DSA từ tệp và trả về
    char* dsa_key = execute_command("cat /tmp/dsa_private.pem");
    unlink(param_filename); // Xóa tệp tạm thời
    return dsa_key;
}