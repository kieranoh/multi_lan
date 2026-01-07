#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // 检查输入参数是否有效
    if (results == NULL) {
        return NULL;
    }
    
    // 创建临时文件模板
    char template[] = "/tmp/results_XXXXXX";
    
    // 使用mkstemp创建唯一的临时文件
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    // 将结果写入文件
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    // 关闭文件描述符
    close(fd);
    
    // 检查写入是否成功
    if (written != (ssize_t)len) {
        // 如果写入失败，删除临时文件
        unlink(template);
        return NULL;
    }
    
    // 动态分配内存来存储文件名
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        // 如果内存分配失败，删除临时文件
        unlink(template);
        return NULL;
    }
    
    // 复制文件名
    strcpy(filename, template);
    
    return filename;
}