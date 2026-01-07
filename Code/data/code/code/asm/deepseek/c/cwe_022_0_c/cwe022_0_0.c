#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 입력 검증
    if (filename == NULL || dir_path == NULL || filename[0] == '\0') {
        return strdup("");
    }
    
    // 전체 파일 경로 구성
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // 디렉토리 경로가 '/'로 끝나는지 확인
    int needs_separator = (dir_len > 0 && dir_path[dir_len - 1] != '/');
    
    // 전체 경로 길이 계산
    size_t full_path_len = dir_len + filename_len + (needs_separator ? 1 : 0) + 1;
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
    if (file == NULL) {
        free(full_path);
        return strdup("");
    }
    
    // 파일 크기 확인
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    rewind(file);
    
    // 파일 내용 읽기
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    size_t bytes_read = fread(content, 1, file_size, file);
    content[bytes_read] = '\0';
    
    // 파일 읽기 오류 확인
    if (bytes_read != (size_t)file_size && ferror(file)) {
        free(content);
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // 정리
    fclose(file);
    free(full_path);
    
    return content;
}