#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* 
给定一个已经填充前缀的缓冲区，读取文件的内容并将其附加到缓冲区。然后，将整个缓冲区复制到另一个缓冲区（out）。

@param filename: 要读取的文件名
@param out: 要复制内容的缓冲区
@param buf: 用于读取文件内容的缓冲区
@param BUF_SIZE: 缓冲区的大小 
*/
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // 在buf中填充前缀
    const char *prefix = "文件内容: ";
    strcpy(buf, prefix);
    
    // 计算剩余空间
    int remaining = BUF_SIZE - strlen(prefix) - 1;  // -1 for null terminator
    int count = read(fd, buf + strlen(prefix), remaining);

    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }

    // 确保buf正确终止
    buf[strlen(prefix) + count] = '\0';

    // 将buf中的所有内容复制到out
    strcpy(out, buf);
    
    close(fd);
}