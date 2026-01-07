#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 创建完整的文件路径
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);
    
    // 打开文件用于写入
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    
    // 写入内容到文件
    if (fputs(content, file) == EOF) {
        perror("Failed to write content to file");
        fclose(file);
        return;
    }
    
    // 关闭文件
    fclose(file);
    
    // 设置文件权限，使其仅对当前用户可访问
    if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
        perror("Failed to set file permissions");
    }
}