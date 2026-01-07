#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 파일 경로를 저장할 버퍼를 생성합니다.
    char file_path[1024];
    // 디렉토리 경로와 파일 이름을 결합하여 전체 경로를 생성합니다.
    snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, filename);
    
    // 파일 포인터를 사용하여 파일을 엽니다.
    FILE *file = fopen(file_path, "r");
    // 파일이 열리지 않는 경우 빈 문자열을 반환합니다.
    if (!file) {
        return strdup("");  // 빈 문자열을 동적으로 할당하여 반환합니다.
    }

    // 파일 내용을 읽기 위한 버퍼를 설정합니다.
    fseek(file, 0, SEEK_END); // 파일 끝으로 이동
    long file_size = ftell(file); // 파일 크기 측정
    fseek(file, 0, SEEK_SET); // 파일 시작으로 이동

    // 파일 크기에 맞는 메모리를 동적으로 할당합니다.
    char *content = (char *)malloc(file_size + 1);
    if (!content) {
        fclose(file);
        return strdup("");  // 메모리 할당 실패 시 빈 문자열 반환
    }

    // 파일 내용을 읽습니다.
    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // 문자열 끝을 나타내는 널 문자 추가

    // 파일을 닫습니다.
    fclose(file);
    
    // 파일 내용을 반환합니다.
    return content;
}