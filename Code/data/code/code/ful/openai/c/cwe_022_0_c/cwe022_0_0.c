#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 파일 경로 생성
    size_t path_length = strlen(dir_path) + strlen(filename) + 2; // 1 for '/', 1 for '\0'
    char *full_path = (char *)malloc(path_length);
    if (full_path == NULL) {
        return NULL; // 메모리 할당 실패
    }
    snprintf(full_path, path_length, "%s/%s", dir_path, filename);
    
    // 파일 열기
    FILE *file = fopen(full_path, "r");
    free(full_path); // 더 이상 필요 없는 full_path 메모리 해제
    if (file == NULL) {
        return strdup(""); // 파일 열기 실패, 빈 문자열 반환
    }

    // 파일 내용 읽기
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char *)malloc(file_size + 1); // 파일 내용용 메모리 할당
    if (content == NULL) {
        fclose(file);
        return NULL; // 메모리 할당 실패
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // 문자열 종료

    fclose(file); // 파일 닫기
    return content; // 파일 내용 반환
}