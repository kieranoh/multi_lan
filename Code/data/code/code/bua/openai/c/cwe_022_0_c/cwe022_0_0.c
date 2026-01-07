#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 파일 경로 생성
    char file_path[1024];
    snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, filename);

    // 파일 열기
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        return strdup(""); // 파일을 열 수 없으면 빈 문자열 반환
    }

    // 파일 크기 계산
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 메모리 할당
    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        fclose(file);
        return strdup(""); // 메모리 할당 실패 시 빈 문자열 반환
    }

    // 파일 내용 읽기
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0'; // 널 종료

    // 파일 닫기
    fclose(file);

    return buffer; // 파일 내용 반환
}