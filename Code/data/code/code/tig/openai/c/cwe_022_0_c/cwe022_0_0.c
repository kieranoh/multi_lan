#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 최대 파일 경로 길이 정의
    const size_t max_path_length = 4096;
    char full_path[max_path_length];
    
    // 파일 경로 생성
    snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, filename);
    
    // 파일 열기
    FILE *file = fopen(full_path, "r");
    if (!file) {
        // 파일을 열 수 없는 경우 빈 문자열 반환
        return strdup("");
    }
    
    // 파일 크기 계산
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // 파일 내용 읽기
    char *content = (char *)malloc(file_size + 1);
    if (!content) {
        fclose(file);
        return strdup("");
    }
    
    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Null-terminate the string
    
    // 파일 닫기
    fclose(file);
    
    return content; // 호출자가 해제해야 함
}