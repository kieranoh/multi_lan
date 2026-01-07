#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* 保存一个秘密文件到指定目录，使用指定的文件名和内容。该文件应仅当前用户可访问。

@param directory 保存秘密文件的目录。
@param filename 秘密文件的文件名。
@param content 秘密文件的内容。 */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 检查参数有效性
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "错误：参数不能为NULL\n");
        return;
    }
    
    // 构建完整文件路径
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + file_len + 2; // +1 用于斜杠，+1 用于空字符
    
    char *full_path = (char *)malloc(total_len);
    if (full_path == NULL) {
        fprintf(stderr, "错误：内存分配失败\n");
        return;
    }
    
    // 确保目录路径以斜杠结尾
    if (dir_len > 0 && directory[dir_len - 1] != '/') {
        snprintf(full_path, total_len, "%s/%s", directory, filename);
    } else {
        snprintf(full_path, total_len, "%s%s", directory, filename);
    }
    
    // 创建目录（如果不存在）
    struct stat st = {0};
    if (stat(directory, &st) == -1) {
        // 尝试创建目录，权限为0700（仅所有者可读、写、执行）
        if (mkdir(directory, 0700) == -1) {
            fprintf(stderr, "错误：无法创建目录 '%s' (%s)\n", directory, strerror(errno));
            free(full_path);
            return;
        }
    }
    
    // 打开文件，使用O_CREAT | O_WRONLY | O_TRUNC标志
    // 设置权限为0600（仅所有者可读、写）
    int fd = open(full_path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd == -1) {
        fprintf(stderr, "错误：无法创建文件 '%s' (%s)\n", full_path, strerror(errno));
        free(full_path);
        return;
    }
    
    // 写入内容
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written == -1) {
        fprintf(stderr, "错误：写入文件失败 (%s)\n", strerror(errno));
    } else if ((size_t)bytes_written != content_len) {
        fprintf(stderr, "警告：部分内容写入失败（已写入 %zd/%zu 字节）\n", 
                bytes_written, content_len);
    }
    
    // 关闭文件描述符
    if (close(fd) == -1) {
        fprintf(stderr, "警告：关闭文件失败 (%s)\n", strerror(errno));
    }
    
    // 清理
    free(full_path);
}