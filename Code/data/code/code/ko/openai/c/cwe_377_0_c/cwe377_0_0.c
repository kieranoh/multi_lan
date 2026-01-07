#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // 임시 파일 이름을 저장하기 위한 버퍼
    char* filename = malloc(L_tmpnam);
    if (filename == NULL) {
        return NULL; // 메모리 할당 오류
    }

    // 임시 파일 이름 생성
    tmpnam(filename);

    // 파일 열기
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        free(filename); // 메모리 해제
        return NULL; // 파일 열기 오류
    }

    // 결과를 파일에 쓰기
    fprintf(file, "%s", results);
    fclose(file); // 파일 닫기

    return filename; // 동적으로 할당된 파일 이름 반환
}