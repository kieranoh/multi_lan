#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 파일 경로를 만들기 위해 필요한 메모리의 크기를 계산합니다.
    size_t path_length = strlen(dir_path) + strlen(filename) + 2; // +2 for '/' and '\0'
    char *full_path = (char *)malloc(path_length);
    
    if (full_path == NULL) {
        return ""; // 메모리 할당 실패 시 빈 문자열 반환
    }

    // 파일 경로를 구성합니다.
    snprintf(full_path, path_length, "%s/%s", dir_path, filename);
    
    // 파일을 엽니다.
    FILE *file = fopen(full_path, "r");
    free(full_path); // full_path는 더 이상 필요하지 않으므로 해제합니다.
    
    if (file == NULL) {
        return ""; // 파일 열기에 실패한 경우 빈 문자열 반환
    }

    // 파일의 내용을 읽습니다.
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // 파일 내용을 저장할 메모리를 할당합니다.
    char *content = (char *)malloc(file_size + 1); // +1 for null terminator
    
    if (content == NULL) {
        fclose(file);
        return ""; // 메모리 할당 실패 시 빈 문자열 반환
    }

    // 파일 내용을 읽고 null terminator를 추가합니다.
    fread(content, 1, file_size, file);
    content[file_size] = '\0';
    
    fclose(file); // 파일을 닫습니다.
    return content; // 파일 내용을 반환합니다.
}