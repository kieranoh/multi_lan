#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Kiểm tra đầu vào
    if (results == NULL) {
        return NULL;
    }
    
    // Tạo tên tệp tạm thời
    char template[] = "/tmp/results_XXXXXX";
    int fd = mkstemp(template);
    
    if (fd == -1) {
        // Không thể tạo tệp tạm thời
        return NULL;
    }
    
    // Ghi nội dung vào tệp
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    if (written != (ssize_t)len) {
        // Ghi không thành công
        close(fd);
        unlink(template); // Xóa tệp tạm thời
        return NULL;
    }
    
    // Đóng tệp
    close(fd);
    
    // Cấp phát bộ nhớ cho tên tệp trả về
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template); // Xóa tệp tạm thời
        return NULL;
    }
    
    strcpy(filename, template);
    return filename;
}