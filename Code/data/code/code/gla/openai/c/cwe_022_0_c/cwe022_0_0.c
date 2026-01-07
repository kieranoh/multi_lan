#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 파일 경로를 생성합니다.
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, filename);
    
    // 파일을 엽니다.
    FILE *file = fopen(filepath, "r");
    if (!file) {
        return strdup(""); // 파일 열기에 실패하면 빈 문자열 반환
    }

    // 파일의 내용을 읽습니다.
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 파일 내용을 저장할 메모리를 할당합니다.
    char *content = malloc(length + 1);
    if (!content) {
        fclose(file);
        return strdup(""); // 메모리 할당 실패 시 빈 문자열 반환
    }

    // 파일 내용을 읽습니다.
    fread(content, 1, length, file);
    content[length] = '\0'; // 널 종료 문자 추가

    fclose(file);
    return content; // 파일 내용 반환
}