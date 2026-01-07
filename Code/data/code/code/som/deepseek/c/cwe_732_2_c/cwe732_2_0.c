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
    if (directory == NULL || filename == NULL || content == NULL) {
        return;
    }

    // 디렉토리 경로와 파일 이름을 결합하여 전체 파일 경로 생성
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    
    // 디렉토리 경로가 '/'로 끝나지 않으면 추가
    int needs_separator = (dir_len > 0 && directory[dir_len - 1] != '/');
    size_t path_len = dir_len + (needs_separator ? 1 : 0) + file_len + 1;
    
    char *full_path = (char *)malloc(path_len);
    if (full_path == NULL) {
        return;
    }
    
    if (needs_separator) {
        snprintf(full_path, path_len, "%s/%s", directory, filename);
    } else {
        snprintf(full_path, path_len, "%s%s", directory, filename);
    }

    // 디렉토리가 존재하지 않으면 생성 (권한: 0700 - 사용자만 읽기/쓰기/실행 가능)
    if (mkdir(directory, 0700) != 0) {
        if (errno != EEXIST) {
            free(full_path);
            return;
        }
    }

    // 파일 생성 및 쓰기 (O_CREAT | O_WRONLY | O_TRUNC - 파일이 없으면 생성, 쓰기 전용, 기존 내용 삭제)
    // 권한: 0600 - 사용자만 읽기/쓰기 가능
    int fd = open(full_path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd == -1) {
        free(full_path);
        return;
    }

    // 내용 쓰기
    size_t content_len = strlen(content);
    ssize_t written = write(fd, content, content_len);
    
    // 파일 닫기
    close(fd);
    free(full_path);
    
    // 쓰기 실패 시 파일 삭제
    if (written != (ssize_t)content_len) {
        unlink(full_path);
    }
}