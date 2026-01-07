#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 检查输入参数是否有效
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "错误：无效的输入参数\n");
        return;
    }
    
    // 创建目录路径
    char *full_path = NULL;
    int path_len = strlen(directory) + strlen(filename) + 2; // +2 用于 '/' 和 '\0'
    
    // 分配内存用于完整路径
    full_path = (char *)malloc(path_len);
    if (full_path == NULL) {
        fprintf(stderr, "错误：内存分配失败\n");
        return;
    }
    
    // 构建完整路径
    snprintf(full_path, path_len, "%s/%s", directory, filename);
    
    // 确保目录存在，如果不存在则创建
    if (mkdir(directory, 0700) != 0) {
        // 如果目录已存在，忽略EEXIST错误
        if (errno != EEXIST) {
            fprintf(stderr, "错误：无法创建目录 '%s' (%s)\n", directory, strerror(errno));
            free(full_path);
            return;
        }
    }
    
    // 创建文件，仅允许所有者读写 (0600)
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        fprintf(stderr, "错误：无法创建文件 '%s' (%s)\n", full_path, strerror(errno));
        free(full_path);
        return;
    }
    
    // 写入内容到文件
    ssize_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written != content_len) {
        fprintf(stderr, "错误：写入文件失败，预期写入 %zd 字节，实际写入 %zd 字节\n", 
                content_len, bytes_written);
        close(fd);
        free(full_path);
        return;
    }
    
    // 关闭文件
    if (close(fd) != 0) {
        fprintf(stderr, "警告：关闭文件时发生错误 (%s)\n", strerror(errno));
    }
    
    // 清理内存
    free(full_path);
}