#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

/* 지정된 디렉토리 경로와 파일 이름을 받아, 디렉토리에서 파일을 읽고 그 내용을 반환합니다. 파일 읽기 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다. 반환된 문자열은 호출자가 해제합니다.

@param filename 사용자가 요청한 읽을 파일의 이름.
@param dir_path 파일이 위치한 디렉토리의 경로.

@return 파일이 존재하고 접근 가능하면 파일의 내용, 그렇지 않으면 빈 문자열. */
char *read_file_from_dir(const char *filename, const char *dir_path) {
    // 입력 매개변수 검증
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // 전체 경로 구성
    size_t dir_len = strlen(dir_path);
    size_t file_len = strlen(filename);
    
    // 경로 구분자 확인 및 추가
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != '/') {
        needs_separator = 1;
    }
    
    // 전체 경로 길이 계산
    size_t full_path_len = dir_len + file_len + needs_separator + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // 전체 경로 생성
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, "/");
    }
    strcat(full_path, filename);
    
    // 파일 존재 및 접근 가능 여부 확인
    struct stat file_stat;
    if (stat(full_path, &file_stat) != 0) {
        free(full_path);
        return strdup("");
    }
    
    // 일반 파일인지 확인
    if (!S_ISREG(file_stat.st_mode)) {
        free(full_path);
        return strdup("");
    }
    
    // 파일 열기
    FILE *file = fopen(full_path, "rb");
    free(full_path);
    
    if (file == NULL) {
        return strdup("");
    }
    
    // 파일 크기 확인
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return strdup("");
    }
    
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        return strdup("");
    }
    
    if (fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return strdup("");
    }
    
    // 메모리 할당 (널 종료 문자를 위한 공간 포함)
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // 파일 내용 읽기
    size_t bytes_read = fread(content, 1, file_size, file);
    fclose(file);
    
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    // 문자열 종료
    content[file_size] = '\0';
    
    return content;
}