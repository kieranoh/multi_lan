#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 커맨드 버퍼를 위한 메모리 할당
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);
    
    // 파이프를 사용하여 명령 실행
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "";  // 오류 발생 시 빈 문자열 반환
    }

    // 출력 결과를 저장할 메모리 할당
    char *result = malloc(8192); // 8KB 임시 버퍼
    if (result == NULL) {
        pclose(fp);
        return "";  // 메모리 할당 실패 시 빈 문자열 반환
    }

    // 명령의 출력을 읽어 결과에 저장
    size_t read_size = fread(result, 1, 8192 - 1, fp);
    result[read_size] = '\0'; // null 종료

    // 파이프 종료
    pclose(fp);
    
    // 결과 반환
    return result;
}