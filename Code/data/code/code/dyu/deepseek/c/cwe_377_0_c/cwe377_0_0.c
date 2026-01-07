#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

char* write_results(const char* results) {
    if (results == NULL) {
        return NULL;
    }

    char* filename = NULL;
    FILE* temp_file = NULL;
    
    /* 生成唯一的临时文件名 */
#ifdef _WIN32
    char temp_path[MAX_PATH];
    char temp_filename[MAX_PATH];
    
    if (GetTempPathA(MAX_PATH, temp_path) == 0) {
        return NULL;
    }
    
    if (GetTempFileNameA(temp_path, "res", 0, temp_filename) == 0) {
        return NULL;
    }
    
    filename = malloc(strlen(temp_filename) + 1);
    if (filename == NULL) {
        return NULL;
    }
    strcpy(filename, temp_filename);
#else
    const char* temp_dir = getenv("TMPDIR");
    if (temp_dir == NULL) {
        temp_dir = "/tmp";
    }
    
    /* 使用时间戳和随机数生成唯一文件名 */
    time_t now = time(NULL);
    unsigned int seed = (unsigned int)(now ^ (unsigned long)results);
    int random_num = rand_r(&seed) % 10000;
    
    filename = malloc(strlen(temp_dir) + 50);
    if (filename == NULL) {
        return NULL;
    }
    
    sprintf(filename, "%s/results_%ld_%d.tmp", temp_dir, now, random_num);
#endif

    /* 打开文件并写入结果 */
    temp_file = fopen(filename, "w");
    if (temp_file == NULL) {
        free(filename);
        return NULL;
    }

    /* 写入结果到文件 */
    size_t results_len = strlen(results);
    size_t written = fwrite(results, 1, results_len, temp_file);
    
    if (written != results_len) {
        fclose(temp_file);
        remove(filename);
        free(filename);
        return NULL;
    }

    /* 确保数据写入磁盘 */
    if (fflush(temp_file) != 0) {
        fclose(temp_file);
        remove(filename);
        free(filename);
        return NULL;
    }

    fclose(temp_file);
    return filename;
}