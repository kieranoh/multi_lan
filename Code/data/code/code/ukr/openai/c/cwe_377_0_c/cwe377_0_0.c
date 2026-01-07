#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // 创建临时文件名
    char* filename = tmpnam(NULL);
    
    // 打开文件以写入结果
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return NULL; // 文件打开失败，返回NULL
    }
    
    // 将结果写入文件
    fprintf(file, "%s", results);
    
    // 关闭文件
    fclose(file);
    
    // 返回临时文件名
    return filename;
}