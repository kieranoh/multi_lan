#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 입력 매개변수 검증
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // 경로 구분자 확인 및 전체 경로 구성
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // 경로가 너무 긴 경우 방지
    if (dir_len + filename_len + 2 > 4096) {
        return strdup("");
    }
    
    // 전체 파일 경로 생성
    char full_path[4096];
    int written;
    
    // 디렉토리 경로가 '/'로 끝나는지 확인
    if (dir_len > 0 && dir_path[dir_len - 1] == '/') {
        written = snprintf(full_path, sizeof(full_path), "%s%s", dir_path, filename);
    } else {
        written = snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, filename);
    }
    
    // snprintf 오류 확인
    if (written < 0 || (size_t)written >= sizeof(full_path)) {
        return strdup("");
    }
    
    // 파일 존재 및 접근 권한 확인
    struct stat path_stat;
    if (stat(full_path, &path_stat) != 0) {
        // 파일을 찾을 수 없거나 접근 권한 오류
        return strdup("");
    }
    
    // 일반 파일인지 확인 (디렉토리나 특수 파일 제외)
    if (!S_ISREG(path_stat.st_mode)) {
        return strdup("");
    }
    
    // 파일 크기 확인 (너무 큰 파일 방지)
    if (path_stat.st_size > 10 * 1024 * 1024) { // 10MB 제한
        return strdup("");
    }
    
    // 파일 열기
    FILE *file = fopen(full_path, "rb");
    if (file == NULL) {
        return strdup("");
    }
    
    // 파일 크기만큼 메모리 할당 (+1 for null terminator)
    char *content = (char *)malloc(path_stat.st_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // 파일 내용 읽기
    size_t bytes_read = fread(content, 1, path_stat.st_size, file);
    
    // 항상 null 종료
    content[bytes_read] = '\0';
    
    // 파일 닫기
    fclose(file);
    
    // 읽은 바이트 수가 예상과 다른 경우
    if (bytes_read != (size_t)path_stat.st_size) {
        free(content);
        return strdup("");
    }
    
    return content;
}