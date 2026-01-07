#include <stdlib.h>
#include <string.h>

/* 根据请求的缓冲区大小，分配一个该大小的缓冲区，并在缓冲区的前10个字节和最后10个字节写入'A'。
@param buf_size: 要分配的缓冲区大小
@return 分配的缓冲区 */
char* allocate_buffer_and_write(size_t buf_size) {
    // 分配缓冲区
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // 分配失败
    }

    // 初始化缓冲区
    memset(buffer, 0, buf_size);

    // 在前10个字节写入'A'
    if (buf_size >= 10) {
        memset(buffer, 'A', 10);
    }

    // 在最后10个字节写入'A'
    if (buf_size >= 10) {
        memset(buffer + buf_size - 10, 'A', 10);
    }

    return buffer; // 返回分配的缓冲区
}