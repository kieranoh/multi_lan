#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 파일 경로 버퍼 할당
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, filename);

    // 파일 포인터 선언
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        // 파일을 열 수 없으면 빈 문자열 반환
        return strdup("");
    }

    // 파일 내용을 읽기
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 파일 크기만큼 메모리 할당
    char *content = (char *)malloc(filesize + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }

    // 파일 내용 읽기
    fread(content, 1, filesize, file);
    content[filesize] = '\0'; // null 종료

    // 파일 닫기
    fclose(file);
    
    return content;
}