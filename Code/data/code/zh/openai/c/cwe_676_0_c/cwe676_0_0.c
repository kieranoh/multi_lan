#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // 处理内存分配失败
    }
    
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // 读取失败，释放内存
        return NULL;
    }
    
    return buf; // 返回读取的缓冲区
}