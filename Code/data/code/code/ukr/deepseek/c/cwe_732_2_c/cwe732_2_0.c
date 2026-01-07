#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 입력 검증
    if (directory == NULL || filename == NULL || content == NULL) {
        return;
    }
    
    // 디렉토리 경로와 파일 이름을 결합하여 전체 경로 생성
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    
    // 경로 구분자 확인 및 추가
    int needs_separator = 0;
    if (dir_len > 0 && directory[dir_len - 1] != '/') {
        needs_separator = 1;
    }
    
    // 전체 경로 길이 계산
    size_t full_path_len = dir_len + file_len + needs_separator + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return;
    }
    
    // 전체 경로 구성
    strcpy(full_path, directory);
    if (needs_separator) {
        strcat(full_path, "/");
    }
    strcat(full_path, filename);
    
    // 디렉토리 존재 확인 및 생성 (필요한 경우)
    struct stat st;
    if (stat(directory, &st) != 0) {
        // 디렉토리가 존재하지 않으면 생성
        if (mkdir(directory, 0700) != 0) {
            free(full_path);
            return;
        }
    } else {
        // 디렉토리가 존재하지만 디렉토리인지 확인
        if (!S_ISDIR(st.st_mode)) {
            free(full_path);
            return;
        }
    }
    
    // 파일 생성 및 쓰기 (O_CREAT | O_EXCL을 사용하여 기존 파일을 덮어쓰지 않도록 함)
    int fd = open(full_path, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
    if (fd == -1) {
        // 파일이 이미 존재하면 실패
        free(full_path);
        return;
    }
    
    // 내용 쓰기
    size_t content_len = strlen(content);
    ssize_t written = write(fd, content, content_len);
    
    // 파일 닫기
    close(fd);
    
    // 메모리 해제
    free(full_path);
    
    // 쓰기 실패 시 파일 삭제
    if (written != (ssize_t)content_len) {
        unlink(full_path);
    }
}