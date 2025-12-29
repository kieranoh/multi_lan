#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 创建一个管道来捕获 ls -l 命令的输出
    FILE *fp;
    char path[1035];
    char *result = NULL;
    size_t total_length = 0;

    // 构建命令字符串
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // 打开管道，执行命令
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // 返回空字符串以指示错误
    }

    // 读取命令输出
    while (fgets(path, sizeof(path), fp) != NULL) {
        size_t len = strlen(path);
        char *new_result = realloc(result, total_length + len + 1);
        if (new_result == NULL) {
            free(result);
            pclose(fp);
            return ""; // 返回空字符串以指示错误
        }
        result = new_result;
        strcpy(result + total_length, path);
        total_length += len;
    }

    // 关闭管道
    if (pclose(fp) == -1) {
        free(result);
        return ""; // 返回空字符串以指示错误
    }

    return result; // 返回包含命令输出的字符串
}