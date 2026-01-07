#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #define PATH_SEPARATOR '\\'
    #define PATH_SEPARATOR_STR "\\"
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #define PATH_SEPARATOR '/'
    #define PATH_SEPARATOR_STR "/"
#endif

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 입력 검증
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // 경로 생성
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // 경로 구분자 확인 및 추가
    int needs_separator = 0;
    if (dir_len > 0) {
        char last_char = dir_path[dir_len - 1];
        if (last_char != '/' && last_char != '\\') {
            needs_separator = 1;
        }
    }
    
    // 전체 경로 길이 계산
    size_t full_path_len = dir_len + filename_len + (needs_separator ? 1 : 0) + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // 전체 경로 구성
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, PATH_SEPARATOR_STR);
    }
    strcat(full_path, filename);
    
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
    
    if (fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return strdup("");
    }
    
    // 메모리 할당 및 파일 읽기
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    size_t bytes_read = fread(content, 1, file_size, file);
    fclose(file);
    
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    content[file_size] = '\0';
    return content;
}