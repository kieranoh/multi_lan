#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 입력 검증
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // 전체 경로 구성
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
    
    // 전체 경로 생성
    if (needs_separator) {
        snprintf(full_path, full_path_len, "%s/%s", dir_path, filename);
    } else {
        snprintf(full_path, full_path_len, "%s%s", dir_path, filename);
    }
    
    // 파일 존재 및 접근 권한 확인
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
    if (file == NULL) {
        free(full_path);
        return strdup("");
    }
    
    // 파일 크기 확인
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (file_size < 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // 메모리 할당 및 파일 읽기
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    size_t bytes_read = fread(content, 1, file_size, file);
    content[bytes_read] = '\0';
    
    // 정리
    fclose(file);
    free(full_path);
    
    return content;
}