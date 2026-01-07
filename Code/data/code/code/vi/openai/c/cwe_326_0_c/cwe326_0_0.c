#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    const int key_length = 2048; // Độ dài khóa 2048 bit
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    // Mở một pipe để thực thi lệnh và đọc đầu ra
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Trả về NULL nếu có lỗi mở pipe
    }

    // Đọc dữ liệu từ pipe
    char *private_key = NULL;
    size_t size = 0;
    ssize_t read;

    // Tạm thời cấp phát bộ nhớ cho chuỗi
    size_t buffer_size = 1024;
    private_key = malloc(buffer_size);
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // Trả về NULL nếu không đủ bộ nhớ
    }

    // Đọc từng dòng từ đầu ra của lệnh
    while ((read = fread(private_key + size, 1, buffer_size - size, fp)) > 0) {
        size += read;
        // Nếu bộ nhớ không đủ, tăng kích thước
        if (size >= buffer_size) {
            buffer_size *= 2;
            private_key = realloc(private_key, buffer_size);
            if (private_key == NULL) {
                pclose(fp);
                return NULL; // Trả về NULL nếu không đủ bộ nhớ
            }
        }
    }

    private_key[size] = '\0'; // Kết thúc chuỗi

    // Đóng pipe
    pclose(fp);
    
    // Trả về khóa riêng được tạo ra
    return private_key;
}