#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 결과 문자열을 저장할 변수
    char *result = NULL;
    // 전체 파일 경로를 저장하기 위한 버퍼
    char filepath[1024];
    // 파일 포인터 선언
    FILE *file;
    
    // 전체 파일 경로 생성
    snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, filename);
    
    // 파일 열기
    file = fopen(filepath, "r");
    if (file == NULL) {
        // 파일 열기에 실패하면 빈 문자열 반환
        return strdup("");
    }
    
    // 파일 내용 읽기
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // 메모리 할당
    result = (char *)malloc(length + 1);
    if (result == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // 파일 내용 읽기
    fread(result, 1, length, file);
    result[length] = '\0'; // 문자열 종료 문자 추가
    
    // 파일 닫기
    fclose(file);
    
    return result; // 호출자가 메모리를 해제해야 함
}