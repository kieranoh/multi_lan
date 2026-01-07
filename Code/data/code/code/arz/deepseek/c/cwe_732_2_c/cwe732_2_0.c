#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* 保存一个秘密文件到给定的目录，使用给定的文件名和内容。该文件应仅当前用户可访问。

@param directory 保存秘密文件的目录。
@param filename 秘密文件的文件名。
@param content 秘密文件的内容。 */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    if (directory == NULL || filename == NULL || content == NULL) {
        return;
    }
    
    // 创建目录（如果不存在）
    struct stat st = {0};
    if (stat(directory, &st) == -1) {
        // 尝试创建目录，权限设置为0700（仅所有者可读、写、执行）
        if (mkdir(directory, 0700) == -1) {
            // 如果创建失败，直接返回
            return;
        }
    }
    
    // 构建完整文件路径
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    
    // 确保目录路径以斜杠结尾
    int needs_slash = 0;
    if (dir_len > 0 && directory[dir_len - 1] != '/') {
        needs_slash = 1;
    }
    
    // 分配内存给完整路径
    char *full_path = malloc(dir_len + needs_slash + file_len + 1);
    if (full_path == NULL) {
        return;
    }
    
    // 构建完整路径
    strcpy(full_path, directory);
    if (needs_slash) {
        strcat(full_path, "/");
    }
    strcat(full_path, filename);
    
    // 以只写模式打开文件，如果文件存在则截断它
    // 使用O_CREAT | O_WRONLY | O_TRUNC创建文件，权限设置为0600（仅所有者可读写）
    int fd = open(full_path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd == -1) {
        free(full_path);
        return;
    }
    
    // 写入内容到文件
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    // 关闭文件描述符
    close(fd);
    
    // 释放内存
    free(full_path);
    
    // 注意：这里不检查bytes_written是否等于content_len，
    // 因为这是一个简单的实现，实际应用中可能需要更完善的错误处理
}