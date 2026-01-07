#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 创建完整的文件路径
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);
    
    // 创建并打开文件进行写入
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("无法创建文件");
        return;
    }
    
    // 写入内容到文件
    fprintf(file, "%s", content);
    fclose(file);
    
    // 更改文件权限，使其仅对当前用户可访问
    if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
        perror("无法更改文件权限");
    }
}