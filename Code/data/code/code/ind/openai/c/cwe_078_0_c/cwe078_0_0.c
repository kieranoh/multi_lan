#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 명령 실행을 위한 버퍼 크기
    size_t buffer_size = 128;
    char *output = malloc(buffer_size);
    if (output == NULL) {
        return "";  // 메모리 할당 실패 시 빈 문자열 반환
    }

    // 커맨드 생성
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);

    // FILE 포인터를 사용하여 커맨드 실행
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        free(output);
        return "";  // popen 실패 시 빈 문자열 반환
    }

    // 출력 결과를 읽어와서 저장
    size_t idx = 0;
    while (fgets(output + idx, buffer_size - idx, fp) != NULL) {
        idx += strlen(output + idx);
        if (idx >= buffer_size - 1) {
            buffer_size *= 2;
            output = realloc(output, buffer_size);
            if (output == NULL) {
                pclose(fp);
                return "";  // 메모리 할당 실패 시 빈 문자열 반환
            }
        }
    }

    // 명령 실행 종료
    pclose(fp);

    // 결과가 없으면 빈 문자열 반환
    if (idx == 0) {
        free(output);
        return "";
    }

    return output;  // 결과 반환
}