#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 파일 경로를 위한 버퍼 할당
    char *full_path = malloc(strlen(dir_path) + strlen(filename) + 2);
    if (!full_path) {
        return ""; // 메모리 할당 실패 시 빈 문자열 반환
    }

    // 경로와 파일 이름 결합
    sprintf(full_path, "%s/%s", dir_path, filename);

    // 파일 열기
    FILE *file = fopen(full_path, "r");
    free(full_path); // 경로 문자열은 더 이상 필요하므로 해제

    if (!file) {
        return ""; // 파일을 열 수 없는 경우 빈 문자열 반환
    }

    // 파일 내용을 읽기
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 내용 저장을 위한 메모리 할당
    char *content = malloc(length + 1);
    if (!content) {
        fclose(file);
        return ""; // 메모리 할당 실패 시 빈 문자열 반환
    }

    // 파일 내용 읽기
    fread(content, 1, length, file);
    content[length] = '\0'; // 문자열 종료

    fclose(file); // 파일 닫기
    return content; // 파일 내용 반환
}