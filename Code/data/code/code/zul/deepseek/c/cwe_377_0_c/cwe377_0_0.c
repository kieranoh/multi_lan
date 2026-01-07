#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/* 임시 파일을 생성하고, 제공된 결과를 그 파일에 작성한 후, 추가 읽기를 위해 파일 이름을 반환합니다. */
char* write_results(const char* results) {
    // 입력 검증
    if (results == NULL) {
        return NULL;
    }
    
    // 임시 파일 이름 생성
    char* filename = malloc(256 * sizeof(char));
    if (filename == NULL) {
        return NULL;
    }
    
    // 타임스탬프와 PID를 사용하여 고유한 파일 이름 생성
    time_t now = time(NULL);
    pid_t pid = getpid();
    snprintf(filename, 256, "temp_results_%ld_%d.txt", (long)now, pid);
    
    // 파일 열기 및 쓰기
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        free(filename);
        return NULL;
    }
    
    // 결과 쓰기
    size_t bytes_written = fwrite(results, sizeof(char), strlen(results), file);
    if (bytes_written != strlen(results)) {
        fclose(file);
        free(filename);
        return NULL;
    }
    
    // 파일 닫기
    if (fclose(file) != 0) {
        free(filename);
        return NULL;
    }
    
    return filename;
}