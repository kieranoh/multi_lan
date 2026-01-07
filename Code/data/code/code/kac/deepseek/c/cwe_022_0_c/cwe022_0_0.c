#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 입력 검증
    if (filename == NULL || dir_path == NULL || strlen(filename) == 0 || strlen(dir_path) == 0) {
        return strdup("");
    }
    
    // 전체 경로 구성
    size_t dir_len = strlen(dir_path);
    size_t file_len = strlen(filename);
    
    // 디렉토리 경로가 '/'로 끝나는지 확인
    int needs_separator = (dir_len > 0 && dir_path[dir_len - 1] != '/');
    
    // 전체 경로 길이 계산
    size_t full_path_len = dir_len + file_len + (needs_separator ? 2 : 1); // +1 for null terminator, +1 for separator if needed
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // 전체 경로 구성
    if (needs_separator) {
        snprintf(full_path, full_path_len, "%s/%s", dir_path, filename);
    } else {
        snprintf(full_path, full_path_len, "%s%s", dir_path, filename);
    }
    
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
    
    // 메모리 할당 (null terminator 공간 포함)
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // 파일 내용 읽기
    size_t bytes_read = fread(content, 1, file_size, file);
    fclose(file);
    
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    // null terminator 추가
    content[file_size] = '\0';
    
    return content;
}