#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 检查输入参数是否有效
    if (filename == NULL || dir_path == NULL) {
        return NULL;
    }
    
    // 构建完整的文件路径
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // 确保目录路径不以斜杠结尾（除非是根目录）
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != '/') {
        needs_separator = 1;
    }
    
    // 分配完整路径的内存
    char *full_path = malloc(dir_len + filename_len + needs_separator + 1);
    if (full_path == NULL) {
        return NULL;
    }
    
    // 构建完整路径
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, "/");
    }
    strcat(full_path, filename);
    
    // 检查文件是否存在且可读
    struct stat file_stat;
    if (stat(full_path, &file_stat) != 0) {
        free(full_path);
        return NULL;
    }
    
    // 检查是否为常规文件
    if (!S_ISREG(file_stat.st_mode)) {
        free(full_path);
        return NULL;
    }
    
    // 检查文件大小（防止读取过大文件）
    if (file_stat.st_size > 100 * 1024 * 1024) { // 限制为100MB
        free(full_path);
        return NULL;
    }
    
    // 打开文件
    FILE *file = fopen(full_path, "rb");
    if (file == NULL) {
        free(full_path);
        return NULL;
    }
    
    // 分配内存存储文件内容
    char *content = malloc(file_stat.st_size + 1);
    if (content == NULL) {
        fclose(file);
        free(full_path);
        return NULL;
    }
    
    // 读取文件内容
    size_t bytes_read = fread(content, 1, file_stat.st_size, file);
    
    // 关闭文件和释放路径内存
    fclose(file);
    free(full_path);
    
    // 检查是否读取了完整的文件
    if (bytes_read != (size_t)file_stat.st_size) {
        free(content);
        return NULL;
    }
    
    // 添加字符串终止符
    content[bytes_read] = '\0';
    
    return content;
}