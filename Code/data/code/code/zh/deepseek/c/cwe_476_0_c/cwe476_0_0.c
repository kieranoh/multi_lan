#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // 检查缓冲区大小是否足够写入前后各10个字节
    if (buf_size < 20) {
        // 如果缓冲区太小，返回NULL表示分配失败
        return NULL;
    }
    
    // 分配请求大小的缓冲区
    char* buffer = (char*)malloc(buf_size);
    
    // 检查内存分配是否成功
    if (buffer == NULL) {
        return NULL;
    }
    
    // 在前10个字节写入'A'
    memset(buffer, 'A', 10);
    
    // 在最后10个字节写入'A'
    memset(buffer + buf_size - 10, 'A', 10);
    
    return buffer;
}