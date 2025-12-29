#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 构建完整的文件路径
    size_t path_len = strlen(dir_path) + strlen(filename) + 2; // 1 for '/', 1 for '\0'
    char *full_path = (char *)malloc(path_len);
    if (full_path == NULL) {
        return NULL; // 内存分配失败
    }
    snprintf(full_path, path_len, "%s/%s", dir_path, filename);

    // 打开文件
    FILE *file = fopen(full_path, "r");
    free(full_path); // 打开文件后释放构建的路径
    if (file == NULL) {
        return ""; // 文件未找到或权限错误，返回空字符串
    }

    // 读取文件内容
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 分配内存以存储文件内容
    char *content = (char *)malloc(file_size + 1); // +1 for '\0'
    if (content == NULL) {
        fclose(file);
        return NULL; // 内存分配失败
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // 确保字符串以'\0'结尾

    fclose(file); // 关闭文件
    return content; // 返回文件内容
}