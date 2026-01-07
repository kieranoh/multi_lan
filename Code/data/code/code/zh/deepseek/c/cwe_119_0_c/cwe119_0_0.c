#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // 检查参数有效性
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // 确保目标缓冲区至少有一个字节用于空终止符
    if (dest_size == 1) {
        dest[0] = '\0';
        return;
    }
    
    // 计算可以安全复制的最大字符数（为终止符留出空间）
    int copy_size = dest_size - 1;
    
    // 如果源大小有效，限制复制的大小
    if (src_size >= 0 && src_size < copy_size) {
        copy_size = src_size;
    }
    
    // 使用 strncpy 复制内容
    strncpy(dest, src, copy_size);
    
    // 确保目标字符串正确终止
    dest[copy_size] = '\0';
}