#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    char *file_path;
    FILE *file;
    long file_size;
    char *content;

    // 디렉토리와 파일 이름을 결합한 전체 경로 생성
    file_path = malloc(strlen(dir_path) + strlen(filename) + 2); // 1 for '/' and 1 for '\0'
    if (file_path == NULL) {
        return ""; // 메모리 할당 실패
    }
    sprintf(file_path, "%s/%s", dir_path, filename);

    // 파일 열기
    file = fopen(file_path, "rb");
    free(file_path);
    if (file == NULL) {
        return ""; // 파일을 열 수 없음
    }

    // 파일 크기 계산
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 파일 내용 읽기
    content = malloc(file_size + 1); // +1 for '\0'
    if (content == NULL) {
        fclose(file);
        return ""; // 메모리 할당 실패
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // 널 종료

    fclose(file);
    return content; // 호출자가 메모리 해제
}