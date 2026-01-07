#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL;
    }
    
    // Đọc một dòng từ stdin vào bộ đệm, tối đa buf_size-1 ký tự
    if (fgets(buf, buf_size, stdin) == NULL) {
        // Nếu không đọc được gì, giải phóng bộ đệm và trả về NULL
        free(buf);
        return NULL;
    }
    
    return buf;
}