#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #define PATH_SEPARATOR '\\'
    #define PATH_SEPARATOR_STR "\\"
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #define PATH_SEPARATOR '/'
    #define PATH_SEPARATOR_STR "/"
#endif

/**
 * 사용자가 제공한 디렉토리 경로와 파일 이름을 받아, 디렉토리에서 파일을 읽고 그 내용을 반환합니다.
 * 파일 읽기 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.
 * 반환된 문자열은 호출자가 해제합니다.
 * 
 * @param filename 사용자가 요청한 읽을 파일의 이름.
 * @param dir_path 파일이 위치한 디렉토리의 경로.
 * 
 * @return 파일이 존재하고 접근 가능하면 파일의 내용, 그렇지 않으면 빈 문자열.
 */
char *read_file_from_dir(const char *filename, const char *dir_path) {
    FILE *file = NULL;
    char *full_path = NULL;
    char *content = NULL;
    long file_size = 0;
    size_t read_size = 0;
    
    // 입력 매개변수 검증
    if (filename == NULL || dir_path == NULL) {
        return strdup("");
    }
    
    // 전체 경로 생성
    size_t dir_len = strlen(dir_path);
    size_t filename_len = strlen(filename);
    
    // 디렉토리 경로가 슬래시로 끝나는지 확인
    int needs_separator = 0;
    if (dir_len > 0 && dir_path[dir_len - 1] != PATH_SEPARATOR) {
        needs_separator = 1;
    }
    
    // 전체 경로 메모리 할당
    full_path = malloc(dir_len + filename_len + needs_separator + 1);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // 경로 구성
    strcpy(full_path, dir_path);
    if (needs_separator) {
        strcat(full_path, PATH_SEPARATOR_STR);
    }
    strcat(full_path, filename);
    
    // 파일 열기
    file = fopen(full_path, "rb");
    if (file == NULL) {
        free(full_path);
        return strdup("");
    }
    
    // 파일 크기 확인
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    rewind(file);
    
    // 파일 내용을 저장할 메모리 할당 (+1 for null terminator)
    content = malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // 파일 내용 읽기
    read_size = fread(content, 1, file_size, file);
    if (read_size != (size_t)file_size) {
        free(content);
        fclose(file);
        free(full_path);
        return strdup("");
    }
    
    // null 종료 문자 추가
    content[file_size] = '\0';
    
    // 정리
    fclose(file);
    free(full_path);
    
    return content;
}