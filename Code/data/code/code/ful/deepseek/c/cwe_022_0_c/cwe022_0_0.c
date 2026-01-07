#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // 경로와 파일명을 결합하여 전체 경로 생성
    size_t dir_len = strlen(dir_path);
    size_t file_len = strlen(filename);
    
    // 경로 구분자 확인 및 추가
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != '/') {
        needs_separator = 1;
    }
    
    // 전체 경로 길이 계산
    size_t full_path_len = dir_len + file_len + needs_separator + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // 전체 경로 구성
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, "/");
    }
    strcat(full_path, filename);
    
    // 파일 존재 및 접근 가능 여부 확인
    struct stat file_stat;
    if (stat(full_path, &file_stat) != 0) {
        free(full_path);
        return strdup("");
    }
    
    // 일반 파일인지 확인
    if (!S_ISREG(file_stat.st_mode)) {
        free(full_path);
        return strdup("");
    }
    
    // 파일 열기
    FILE *file = fopen(full_path, "rb");
    free(full_path);
    
    if (file == NULL) {
        return strdup("");
    }
    
    // 파일 크기 확인
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (file_size <= 0) {
        fclose(file);
        return strdup("");
    }
    
    // 파일 내용 읽기
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