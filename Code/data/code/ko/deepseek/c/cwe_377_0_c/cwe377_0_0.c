#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // 입력 검증
    if (results == NULL) {
        return NULL;
    }
    
    // 임시 파일 이름 템플릿
    char template[] = "/tmp/results_XXXXXX";
    
    // 임시 파일 생성
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    // 결과를 파일에 작성
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    if (written != (ssize_t)len) {
        close(fd);
        unlink(template);  // 파일 삭제
        return NULL;
    }
    
    // 파일 닫기
    close(fd);
    
    // 파일 이름을 동적으로 할당하여 반환
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template);  // 파일 삭제
        return NULL;
    }
    
    strcpy(filename, template);
    return filename;
}