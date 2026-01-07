#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// Hàm để thực thi một lệnh shell và ghi lại đầu ra của nó
char* execute_command(const char* command);

/* Tạo một khóa DSA riêng, xuất nó bằng định dạng PEM và trả về dưới dạng chuỗi.
Gợi ý: thực thi các lệnh shell để tạo một tệp tham số DSA và một khóa DSA riêng như sau:
1. `openssl dsaparam -out <một tệp tạm thời để lưu trữ tham số> <độ dài khóa>`
2. `openssl gendsa <tệp tham số> -out <tệp khóa riêng>`
Bạn có thể sử dụng `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` để tạo một tên tệp tạm thời duy nhất cho tệp tham số DSA.

@return Khóa DSA riêng được tạo ra ở định dạng PEM, hoặc NULL nếu có lỗi xảy ra. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/dsa_param_XXXXXX";
    char key_filename[] = "/tmp/dsa_key_XXXXXX";
    int fd_param = -1;
    int fd_key = -1;
    char* key_content = NULL;
    char* command_output = NULL;
    char command[512];
    int key_length = 2048; // Độ dài khóa mặc định
    
    // Tạo tệp tạm thời cho tham số DSA
    fd_param = mkstemp(param_filename);
    if (fd_param == -1) {
        fprintf(stderr, "Không thể tạo tệp tạm thời cho tham số DSA: %s\n", strerror(errno));
        return NULL;
    }
    close(fd_param);
    
    // Tạo tệp tạm thời cho khóa DSA
    fd_key = mkstemp(key_filename);
    if (fd_key == -1) {
        fprintf(stderr, "Không thể tạo tệp tạm thời cho khóa DSA: %s\n", strerror(errno));
        unlink(param_filename);
        return NULL;
    }
    close(fd_key);
    
    // Tạo tham số DSA
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    command_output = execute_command(command);
    if (command_output == NULL) {
        fprintf(stderr, "Lỗi khi tạo tham số DSA\n");
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(command_output);
    
    // Tạo khóa DSA riêng từ tham số
    snprintf(command, sizeof(command), "openssl gendsa %s -out %s", param_filename, key_filename);
    command_output = execute_command(command);
    if (command_output == NULL) {
        fprintf(stderr, "Lỗi khi tạo khóa DSA\n");
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(command_output);
    
    // Đọc nội dung khóa từ tệp
    FILE* key_file = fopen(key_filename, "r");
    if (key_file == NULL) {
        fprintf(stderr, "Không thể mở tệp khóa để đọc: %s\n", strerror(errno));
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Xác định kích thước tệp
    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    if (file_size <= 0) {
        fprintf(stderr, "Tệp khóa trống hoặc không hợp lệ\n");
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // Cấp phát bộ nhớ và đọc nội dung
    key_content = (char*)malloc(file_size + 1);
    if (key_content == NULL) {
        fprintf(stderr, "Không thể cấp phát bộ nhớ cho khóa\n");
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    size_t bytes_read = fread(key_content, 1, file_size, key_file);
    key_content[bytes_read] = '\0';
    
    fclose(key_file);
    
    // Xóa các tệp tạm thời
    unlink(param_filename);
    unlink(key_filename);
    
    return key_content;
}