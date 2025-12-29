#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Tạo tên tệp tạm thời
    char* filename = malloc(256);
    if (!filename) {
        return NULL; // Nếu không cấp phát được bộ nhớ, trả về NULL
    }
    
    // Tạo tên tệp với tiền tố /tmp/ và ID quá trình
    snprintf(filename, 256, "/tmp/results_%d.txt", getpid());
    
    // Mở tệp để ghi
    FILE* file = fopen(filename, "w");
    if (!file) {
        free(filename); // Giải phóng bộ nhớ nếu không mở được tệp
        return NULL;
    }

    // Ghi kết quả vào tệp
    fwrite(results, sizeof(char), strlen(results), file);
    
    // Đóng tệp
    fclose(file);
    
    // Trả về tên tệp tạm thời
    return filename;
}