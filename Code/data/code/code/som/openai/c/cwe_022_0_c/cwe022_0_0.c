#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 파일 경로를 저장할 버퍼
    char filepath[1024];
    
    // 디렉토리 경로와 파일 이름을 결합하여 전체 파일 경로 생성
    snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, filename);

    // 파일 포인터 선언
    FILE *file = fopen(filepath, "r");
    if (!file) {
        // 파일 열기에 실패하면 빈 문자열 반환
        return strdup("");
    }

    // 파일의 내용을 읽기 위한 버퍼
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 파일 내용을 저장할 메모리 할당
    char *content = (char *)malloc(filesize + 1);
    if (!content) {
        fclose(file);
        return strdup(""); // 메모리 할당 실패 시 빈 문자열 반환
    }

    // 파일에서 내용 읽기
    fread(content, 1, filesize, file);
    content[filesize] = '\0'; // null 문자 추가

    // 파일 닫기
    fclose(file);

    return content; // 읽은 내용 반환
}