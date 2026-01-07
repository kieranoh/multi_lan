#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 파일 경로를 저장하기 위한 버퍼
    char filepath[1024];
    // 파일 포인터
    FILE *file;
    
    // 파일 경로 생성
    snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, filename);
    
    // 파일 열기
    file = fopen(filepath, "r");
    if (file == NULL) {
        // 파일 열기에 실패하면 빈 문자열 반환
        return strdup("");
    }
    
    // 파일 내용을 읽기 위한 버퍼
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // 파일 내용을 저장할 메모리 할당
    char *content = malloc(filesize + 1);
    if (content == NULL) {
        fclose(file);
        return strdup(""); // 메모리 할당 실패 시 빈 문자열 반환
    }
    
    // 파일 내용 읽기
    fread(content, 1, filesize, file);
    content[filesize] = '\0'; // 널 종료
    
    // 파일 닫기
    fclose(file);
    
    return content; // 호출자가 해제해야 함
}