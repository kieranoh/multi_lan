#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    char* temp_filename = NULL;
    FILE* temp_file = NULL;

    // 创建一个临时文件名
    char template[] = "/tmp/resultsXXXXXX"; // 使用 XXXXXX 作为占位符
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL; // 如果创建临时文件失败，返回 NULL
    }

    // 将文件名存入动态分配的字符串
    temp_filename = strdup(template);
    if (temp_filename == NULL) {
        close(fd);
        unlink(template); // 删除临时文件
        return NULL; // 动态分配失败，返回 NULL
    }

    // 以写模式打开临时文件
    temp_file = fdopen(fd, "w");
    if (temp_file == NULL) {
        free(temp_filename);
        unlink(template); // 删除临时文件
        return NULL; // 打开文件失败，返回 NULL
    }

    // 将结果写入临时文件
    if (fprintf(temp_file, "%s", results) < 0) {
        fclose(temp_file);
        free(temp_filename);
        unlink(template); // 删除临时文件
        return NULL; // 写入失败，返回 NULL
    }

    // 关闭文件
    fclose(temp_file);

    // 返回临时文件名
    return temp_filename;
}