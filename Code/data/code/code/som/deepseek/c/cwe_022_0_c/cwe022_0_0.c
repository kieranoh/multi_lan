#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #define PATH_SEPARATOR '\\'
#else
    #include <sys/stat.h>
    #include <unistd.h>
    #define PATH_SEPARATOR '/'
#endif

char *read_file_from_dir(const char *filename, const char *dir_path) {
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // 전체 경로 구성
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    size_t total_len = dir_len + filename_len + 2; // +1 for separator, +1 for null terminator
    
    char *full_path = (char *)malloc(total_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // 경로 구성
    snprintf(full_path, total_len, "%s%c%s", dir_path, PATH_SEPARATOR, filename);
    
    // 파일 열기
    FILE *file = fopen(full_path, "rb");
    free(full_path);
    
    if (file == NULL) {
        return strdup("");
    }
    
    // 파일 크기 확인
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return strdup("");
    }
    
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        return strdup("");
    }
    
    rewind(file);
    
    // 메모리 할당
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // 파일 읽기
    size_t bytes_read = fread(content, 1, file_size, file);
    fclose(file);
    
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    content[file_size] = '\0';
    return content;
}