#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/* 保存一个秘密文件到给定的目录，使用给定的文件名和内容。该文件应仅当前用户可访问。

@param directory 保存秘密文件的目录。
@param filename 秘密文件的文件名。
@param content 秘密文件的内容。 */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    if (directory == NULL || filename == NULL || content == NULL) {
        return;
    }
    
    // 构建完整路径
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    
    // 检查是否需要路径分隔符
    int needs_separator = 0;
    if (dir_len > 0 && directory[dir_len - 1] != '/') {
        needs_separator = 1;
    }
    
    // 分配完整路径缓冲区
    size_t full_path_len = dir_len + file_len + (needs_separator ? 1 : 0) + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return;
    }
    
    // 构建完整路径
    strcpy(full_path, directory);
    if (needs_separator) {
        strcat(full_path, "/");
    }
    strcat(full_path, filename);
    
    // 确保目录存在
    struct stat st;
    if (stat(directory, &st) != 0) {
        // 目录不存在，尝试创建
        if (mkdir(directory, 0700) != 0) {
            free(full_path);
            return;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        // 存在但不是目录
        free(full_path);
        return;
    }
    
    // 创建文件，仅允许所有者读写 (0600)
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        free(full_path);
        return;
    }
    
    // 写入内容
    size_t content_len = strlen(content);
    ssize_t written = write(fd, content, content_len);
    
    // 确保文件权限正确 (以防万一)
    fchmod(fd, 0600);
    
    close(fd);
    free(full_path);
}