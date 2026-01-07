#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 명령어 버퍼 크기
    const size_t buffer_size = 4096;
    char command[buffer_size];
    
    // 결과를 저장할 버퍼
    char *result = (char *)malloc(buffer_size);
    if (result == NULL) {
        return ""; // 메모리 할당 실패 시 빈 문자열 반환
    }
    
    // ls -l 명령어 구성
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);
    
    // 파일 스트림을 통해 명령 실행
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        free(result);
        return ""; // 명령 실행 실패 시 빈 문자열 반환
    }
    
    // 명령의 출력을 읽는다
    size_t total_read = 0;
    size_t bytes_read;
    while ((bytes_read = fread(result + total_read, 1, buffer_size - total_read - 1, fp)) > 0) {
        total_read += bytes_read;
        if (total_read >= buffer_size - 1) {
            break; // 버퍼 크기를 초과하지 않도록 방지
        }
    }
    
    result[total_read] = '\0'; // 문자열 종료

    // 명령 종료
    pclose(fp);

    return result; // 결과 반환
}