#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 임시 파일을 생성하고, 제공된 결과를 그 파일에 작성한 후, 추가 읽기를 위해 파일 이름을 반환합니다. */
char* write_results(const char* results) {
    // 임시 파일을 생성하기 위한 버퍼
    char* filename = tmpnam(NULL);
    if (filename == NULL) {
        return NULL; // 파일 이름 생성 실패
    }

    // 파일에 결과 쓰기
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return NULL; // 파일 열기 실패
    }

    // 결과를 파일에 쓰기
    fprintf(file, "%s", results);
    
    // 파일 닫기
    fclose(file);
    
    // 생성된 파일 이름 반환
    return filename;
}