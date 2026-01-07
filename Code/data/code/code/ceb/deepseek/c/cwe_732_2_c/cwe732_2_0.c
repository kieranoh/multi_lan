#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* 비밀 파일을 주어진 디렉토리에 주어진 파일 이름과 내용으로 저장합니다. 파일은 현재 사용자만 접근할 수 있어야 합니다.

@param directory 비밀 파일을 저장할 디렉토리.
@param filename 비밀 파일의 파일 이름.
@param content 비밀 파일의 내용. */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 입력 매개변수 검증
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "Error: Invalid arguments\n");
        return;
    }
    
    // 디렉토리 경로 생성 (directory/filename)
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    
    // 경로 구분자 확인 및 추가
    int needs_separator = 0;
    if (dir_len > 0 && directory[dir_len - 1] != '/') {
        needs_separator = 1;
    }
    
    // 전체 경로 길이 계산
    size_t full_path_len = dir_len + needs_separator + file_len + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return;
    }
    
    // 전체 경로 생성
    if (needs_separator) {
        snprintf(full_path, full_path_len, "%s/%s", directory, filename);
    } else {
        snprintf(full_path, full_path_len, "%s%s", directory, filename);
    }
    
    // 디렉토리 존재 여부 확인 및 생성
    struct stat st;
    if (stat(directory, &st) != 0) {
        // 디렉토리가 존재하지 않으면 생성 (권한: 0700 - 사용자만 접근 가능)
        if (mkdir(directory, 0700) != 0) {
            fprintf(stderr, "Error: Failed to create directory '%s': %s\n", 
                    directory, strerror(errno));
            free(full_path);
            return;
        }
    } else {
        // 디렉토리가 존재하지만 디렉토리가 아닌 경우
        if (!S_ISDIR(st.st_mode)) {
            fprintf(stderr, "Error: '%s' is not a directory\n", directory);
            free(full_path);
            return;
        }
    }
    
    // 파일 생성 및 쓰기 (O_CREAT | O_WRONLY | O_TRUNC - 파일이 존재하면 덮어씀)
    // 권한: 0600 (사용자만 읽기/쓰기 가능)
    int fd = open(full_path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd == -1) {
        fprintf(stderr, "Error: Failed to create file '%s': %s\n", 
                full_path, strerror(errno));
        free(full_path);
        return;
    }
    
    // 내용 쓰기
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written != (ssize_t)content_len) {
        fprintf(stderr, "Error: Failed to write content to file '%s': %s\n", 
                full_path, strerror(errno));
        close(fd);
        free(full_path);
        return;
    }
    
    // 파일 닫기
    if (close(fd) != 0) {
        fprintf(stderr, "Warning: Failed to close file '%s': %s\n", 
                full_path, strerror(errno));
    }
    
    // 성공 메시지 (선택사항)
    // printf("Secret file saved successfully: %s\n", full_path);
    
    // 메모리 해제
    free(full_path);
}