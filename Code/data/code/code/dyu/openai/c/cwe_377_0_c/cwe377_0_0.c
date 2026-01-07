#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* write_results(const char* results) {
    // 创建一个临时文件名
    char* temp_filename = tmpnam(NULL);
    if (temp_filename == NULL) {
        return NULL; // 如果无法生成临时文件名，则返回 NULL
    }

    // 打开文件以写入结果
    FILE* file = fopen(temp_filename, "w");
    if (file == NULL) {
        return NULL; // 如果无法打开文件，则返回 NULL
    }

    // 将结果写入文件
    fprintf(file, "%s", results);

    // 关闭文件
    fclose(file);

    // 返回临时文件名
    return temp_filename;
}