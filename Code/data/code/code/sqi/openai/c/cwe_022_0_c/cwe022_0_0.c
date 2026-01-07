#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 파일 경로를 위한 버퍼를 생성합니다.
    char file_path[1024];
    snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, filename);

    // 파일을 읽기 모드로 엽니다.
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        // 파일 열기에 실패하면 빈 문자열을 반환합니다.
        return strdup("");
    }

    // 파일의 내용을 읽기 위한 버퍼를 초기화합니다.
    fseek(file, 0, SEEK_END); // 파일의 끝으로 이동합니다.
    long file_size = ftell(file); // 파일 크기를 가져옵니다.
    fseek(file, 0, SEEK_SET); // 파일의 시작으로 다시 이동합니다.

    // 파일 크기에 맞춰 메모리를 할당합니다.
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup(""); // 메모리 할당 실패 시 빈 문자열 반환
    }

    // 파일 내용을 읽습니다.
    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // 문자열의 끝을 표시합니다.

    // 파일을 닫습니다.
    fclose(file);
    
    return content; // 파일의 내용을 반환합니다.
}