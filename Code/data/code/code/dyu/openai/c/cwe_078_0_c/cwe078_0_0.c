#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char *get_ls_result(const char *dir_path) {
    // 파이프를 통해 ls -l 명령의 출력을 읽기 위해 FILE 포인터 선언
    FILE *fp;
    // 출력 내용을 저장할 동적 메모리 할당
    char *result = malloc(BUFFER_SIZE);
    if (result == NULL) {
        return ""; // 메모리 할당 실패 시 빈 문자열 반환
    }
    
    // 명령어를 실행하고 결과를 파이프를 통해 읽기
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);
    
    fp = popen(command, "r");
    if (fp == NULL) {
        free(result);
        return ""; // 명령 실행 실패 시 빈 문자열 반환
    }

    // 결과를 읽어들임
    size_t total_read = 0;
    size_t bytes_read;
    while ((bytes_read = fread(result + total_read, 1, BUFFER_SIZE - total_read, fp)) > 0) {
        total_read += bytes_read;
        // 만약 공간이 부족하다면 더 큰 공간으로 재할당
        if (total_read >= BUFFER_SIZE) {
            result = realloc(result, total_read + BUFFER_SIZE);
            if (result == NULL) {
                pclose(fp);
                return ""; // 메모리 재할당 실패 시 빈 문자열 반환
            }
        }
    }
    
    // 파일 포인터 닫기
    pclose(fp);
    
    // 문자열 끝을 표시
    result[total_read] = '\0';
    
    // 결과 반환
    return result;
}