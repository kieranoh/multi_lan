#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 파일 경로를 저장할 버퍼
    char filepath[1024];
    FILE *file;
    size_t filesize;
    char *buffer;

    // 디렉토리 경로와 파일 이름을 결합하여 전체 파일 경로 생성
    snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, filename);

    // 파일을 열기
    file = fopen(filepath, "r");
    if (file == NULL) {
        // 파일을 열 수 없으면 빈 문자열 반환
        return strdup("");
    }

    // 파일 크기 계산
    fseek(file, 0, SEEK_END);
    filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 파일 내용을 저장할 메모리 할당
    buffer = (char *)malloc(filesize + 1);
    if (buffer == NULL) {
        fclose(file);
        return strdup("");
    }

    // 파일 내용 읽기
    fread(buffer, 1, filesize, file);
    buffer[filesize] = '\0'; // null terminator 추가

    // 파일 닫기
    fclose(file);

    return buffer; // 호출자가 해제해야 하는 문자열 반환
}