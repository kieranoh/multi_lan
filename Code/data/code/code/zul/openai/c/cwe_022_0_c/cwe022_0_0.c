#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 파일 경로를 위한 버퍼를 할당합니다.
    char *file_path = malloc(strlen(dir_path) + strlen(filename) + 2); // +2 for '/' and '\0'
    if (!file_path) {
        return NULL; // 메모리 할당 실패
    }
    
    // 파일 경로를 만듭니다.
    sprintf(file_path, "%s/%s", dir_path, filename);

    // 파일 포인터를 선언합니다.
    FILE *file = fopen(file_path, "r");
    free(file_path); // 경로가 더 이상 필요하지 않으므로 해제합니다.
    if (!file) {
        return ""; // 파일을 열 수 없으면 빈 문자열 반환
    }

    // 파일 내용을 읽기 위한 버퍼를 할당합니다.
    char *buffer = NULL;
    size_t size = 0;
    ssize_t read;

    // 파일을 한 줄씩 읽어 내용을 할당합니다.
    while ((read = getline(&buffer, &size, file)) != -1) {
        // 실제 내용이 있는 경우
        // 추가적인 로직이 필요할 수 있습니다.
    }

    fclose(file); // 파일을 닫습니다.
    
    // 파일 내용이 없으면 빈 문자열 반환
    if (!buffer) {
        return "";
    }

    return buffer; // 호출자가 해제해야 함
}