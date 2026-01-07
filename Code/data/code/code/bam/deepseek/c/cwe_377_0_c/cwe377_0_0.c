#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #include <io.h>
    #define access _access
    #define F_OK 0
#else
    #include <unistd.h>
#endif

char* write_results(const char* results) {
    /* 创建一个临时文件，将提供的结果写入其中，并返回文件名以供进一步读取。 */
    
    if (results == NULL) {
        return NULL;
    }
    
    char* filename = NULL;
    FILE* temp_file = NULL;
    
    /* 生成唯一的临时文件名 */
#ifdef _WIN32
    char temp_path[MAX_PATH];
    char temp_name[MAX_PATH];
    
    /* 获取临时目录路径 */
    if (GetTempPathA(MAX_PATH, temp_path) == 0) {
        return NULL;
    }
    
    /* 生成唯一的临时文件名 */
    if (GetTempFileNameA(temp_path, "res", 0, temp_name) == 0) {
        return NULL;
    }
    
    filename = malloc(strlen(temp_name) + 1);
    if (filename == NULL) {
        return NULL;
    }
    strcpy(filename, temp_name);
    
#else
    /* Unix/Linux系统使用mkstemp创建安全的临时文件 */
    char template[] = "/tmp/results_XXXXXX";
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        close(fd);
        return NULL;
    }
    strcpy(filename, template);
    
    /* 将文件描述符转换为FILE指针 */
    temp_file = fdopen(fd, "w");
    if (temp_file == NULL) {
        free(filename);
        close(fd);
        return NULL;
    }
#endif
    
    /* 如果不是通过mkstemp创建的，则打开文件 */
#ifndef _WIN32
    /* 已经通过mkstemp打开了文件 */
#else
    temp_file = fopen(filename, "w");
    if (temp_file == NULL) {
        free(filename);
        return NULL;
    }
#endif
    
    /* 将结果写入文件 */
    size_t results_len = strlen(results);
    size_t written = fwrite(results, 1, results_len, temp_file);
    
    if (written != results_len) {
        fclose(temp_file);
        free(filename);
        return NULL;
    }
    
    /* 确保数据写入磁盘 */
    if (fflush(temp_file) != 0) {
        fclose(temp_file);
        free(filename);
        return NULL;
    }
    
    /* 关闭文件 */
    if (fclose(temp_file) != 0) {
        free(filename);
        return NULL;
    }
    
    /* 验证文件是否成功创建并包含数据 */
    if (access(filename, F_OK) != 0) {
        free(filename);
        return NULL;
    }
    
    return filename;
}