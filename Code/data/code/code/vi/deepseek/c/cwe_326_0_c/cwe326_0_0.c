#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Tạo một khóa RSA riêng, xuất nó bằng định dạng PEM và trả về dưới dạng chuỗi.
Thực hiện lệnh "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" để tạo khóa.

@return Khóa RSA riêng được tạo ra ở định dạng PEM, hoặc NULL nếu có lỗi xảy ra. */
char *create_private_key() {
    // Độ dài khóa mặc định là 2048 bits
    const int key_length = 2048;
    
    // Tạo lệnh với độ dài khóa được chỉ định
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // Mở pipe để đọc đầu ra từ lệnh
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    // Đọc đầu ra từ lệnh
    char buffer[4096];
    size_t total_size = 0;
    char *private_key = NULL;
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t chunk_size = strlen(buffer);
        char *temp = realloc(private_key, total_size + chunk_size + 1);
        if (temp == NULL) {
            free(private_key);
            pclose(fp);
            return NULL;
        }
        private_key = temp;
        memcpy(private_key + total_size, buffer, chunk_size);
        total_size += chunk_size;
        private_key[total_size] = '\0';
    }
    
    // Đóng pipe và kiểm tra trạng thái thoát
    int status = pclose(fp);
    if (status != 0 || private_key == NULL || total_size == 0) {
        free(private_key);
        return NULL;
    }
    
    return private_key;
}