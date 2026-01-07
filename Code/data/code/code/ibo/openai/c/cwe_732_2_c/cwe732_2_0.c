#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 创建完整的文件路径
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // 创建并打开文件
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("无法打开文件");
        return;
    }

    // 写入内容
    if (fputs(content, file) == EOF) {
        perror("写入文件时出错");
        fclose(file);
        return;
    }

    // 关闭文件
    fclose(file);

    // 设置文件权限为 600（仅当前用户可读写）
    if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
        perror("设置文件权限时出错");
    }
}