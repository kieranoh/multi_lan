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
    size_t total_len = dir_len + file_len + 2; // '/' + 널 종결자
    
    char *full_path = (char *)malloc(total_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // 경로 구성
    snprintf(full_path, total_len, "%s/%s", dir_path, filename);
    
    // 파일 존재 및 접근 가능 여부 확인
    struct stat path_stat;
    if (stat(full_path, &path_stat) != 0) {
        free(full_path);
        return strdup("");
    }
    
    // 일반 파일인지 확인
    if (!S_ISREG(path_stat.st_mode)) {
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
    
    // 메모리 할당 (널 종결자를 위한 +1)
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // 파일 내용 읽기
    size_t bytes_read = fread(content, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        free(content);
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // 널 종결자 추가
    content[file_size] = '\0';
    
    // 정리
    fclose(file);
    free(full_path);
    
    return content;
}