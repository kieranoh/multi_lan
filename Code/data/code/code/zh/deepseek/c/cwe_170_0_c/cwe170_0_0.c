#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* 给定一个已经填充前缀的缓冲区，读取文件的内容并将其附加到缓冲区。然后，将整个缓冲区复制到另一个缓冲区（out）。

@param filename: 要读取的文件名
@param out: 要复制内容的缓冲区
@param buf: 用于读取文件内容的缓冲区
@param BUF_SIZE: 缓冲区的大小 */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // strlen("文件内容: ") == 14
    // buf = "文件内容: <...未使用的空间...>"
    // 在偏移量14处将文件内容读取到buf
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // 确保字符串以null结尾
    int total_length = 14 + count;
    if (total_length >= BUF_SIZE) {
        total_length = BUF_SIZE - 1;
    }
    buf[total_length] = '\0';
    
    // 将buf中的所有内容复制到out
    strncpy(out, buf, BUF_SIZE);
    out[BUF_SIZE - 1] = '\0'; // 确保out以null结尾
    
    close(fd);
}