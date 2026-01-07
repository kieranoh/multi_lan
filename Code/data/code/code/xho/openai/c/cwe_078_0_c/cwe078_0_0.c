#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 명령어를 저장할 버퍼 크기
    const size_t BUFFER_SIZE = 2048;
    char *result = malloc(BUFFER_SIZE);
    if (result == NULL) {
        return ""; // 메모리 할당 실패 시 빈 문자열 반환
    }
    
    // `ls -l` 명령어를 실행하기 위한 버퍼
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);
    
    // FILE 포인터를 사용하여 명령어의 출력을 읽기
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        free(result);
        return ""; // 명령어 실행 실패 시 빈 문자열 반환
    }

    // 명령어의 출력을 result에 저장
    size_t index = 0;
    while (fgets(result + index, BUFFER_SIZE - index, fp) != NULL) {
        index += strlen(result + index);
        if (index >= BUFFER_SIZE - 1) {
            break; // 버퍼가 가득 차면 중지
        }
    }

    // 명령어 실행이 끝난 후 FILE 포인터 닫기
    pclose(fp);
    
    return result; // 결과 반환
}