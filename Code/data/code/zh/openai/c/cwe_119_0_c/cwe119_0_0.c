#include <stdio.h>
#include <string.h>

/* 使用 strncpy 尽可能多地将 src 的内容复制到 dest

@param dest: 目标缓冲区
@param dest_size: 目标缓冲区的大小
@param src: 源缓冲区
@param src_size: 源缓冲区的大小 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // 确保目标缓冲区和源缓冲区的大小大于0
    if (dest_size <= 0 || src_size <= 0) {
        return;
    }

    // 计算要复制的实际字节数
    int bytes_to_copy = (src_size < dest_size - 1) ? src_size : dest_size - 1;

    // 使用 strncpy 复制数据
    strncpy(dest, src, bytes_to_copy);

    // 确保目标字符串以 null 结尾
    dest[bytes_to_copy] = '\0';
}