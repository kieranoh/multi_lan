#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 파일 경로를 저장하기 위한 버퍼를 할당
    char *file_path = malloc(strlen(dir_path) + strlen(filename) + 2); // +2 for "/" and null terminator
    if (file_path == NULL) {
        return NULL; // 메모리 할당 오류
    }

    // 파일 경로 생성
    sprintf(file_path, "%s/%s", dir_path, filename);

    // 파일 포인터 선언
    FILE *file = fopen(file_path, "r");
    free(file_path); // 파일 경로는 더 이상 필요 없음

    if (file == NULL) {
        return ""; // 파일을 찾을 수 없거나 접근 권한 오류
    }

    // 파일 내용을 저장할 버퍼를 할당
    char *content = malloc(1024); // 예시로 1024자까지 읽을 수 있도록 할당
    if (content == NULL) {
        fclose(file);
        return ""; // 메모리 할당 오류
    }

    // 파일 내용을 읽기
    size_t size = fread(content, 1, 1024, file);
    content[size] = '\0'; // 문자열 종료 문자 추가

    fclose(file); // 파일 닫기

    return content; // 파일 내용 반환
}