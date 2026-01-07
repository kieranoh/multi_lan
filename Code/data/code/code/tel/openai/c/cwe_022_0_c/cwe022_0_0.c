#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 파일 경로를 저장할 버퍼
    char file_path[1024];
    snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, filename);

    // 파일 포인터
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        // 파일을 열 수 없으면 빈 문자열 반환
        return strdup("");
    }

    // 파일의 내용을 읽기 위한 버퍼
    char *content = NULL;
    size_t size = 0;
    size_t read_size;

    // 파일의 내용을 읽기
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 메모리 할당
    content = (char *)malloc(size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }

    // 파일 내용 읽기
    read_size = fread(content, 1, size, file);
    content[read_size] = '\0'; // Null-terminate the string

    // 파일 닫기
    fclose(file);

    return content;
}