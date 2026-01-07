#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 파일 경로를 저장할 버퍼
    char file_path[1024];
    
    // 디렉토리 경로와 파일 이름을 결합하여 전체 파일 경로 생성
    snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, filename);
    
    // 파일 포인터 초기화
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        // 파일을 열 수 없으면 빈 문자열 반환
        return strdup("");
    }

    // 파일의 내용을 읽기 위한 버퍼
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 파일의 내용을 저장할 메모리 할당
    char *content = malloc(length + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }

    // 파일 내용을 읽음
    fread(content, 1, length, file);
    content[length] = '\0'; // 문자열 종료

    // 파일 닫기
    fclose(file);

    return content;
}