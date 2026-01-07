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
    
    // 디렉토리 경로가 '/'로 끝나는지 확인
    int needs_separator = (dir_len > 0 && directory[dir_len - 1] != '/');
    
    // 전체 경로를 위한 메모리 할당
    size_t full_path_len = dir_len + file_len + (needs_separator ? 1 : 0) + 1;
    char *full_path = (char *)malloc(full_path_len);
    if (full_path == NULL) {
        return;
    }
    
    // 전체 경로 구성
    if (needs_separator) {
        snprintf(full_path, full_path_len, "%s/%s", directory, filename);
    } else {
        snprintf(full_path, full_path_len, "%s%s", directory, filename);
    }

    // 디렉토리가 존재하지 않으면 생성 (0700 권한으로)
    struct stat st;
    if (stat(directory, &st) != 0) {
        if (mkdir(directory, 0700) != 0) {
            free(full_path);
            return;
        }
    } else if (!S_ISDIR(st.st_mode)) {
        // 디렉토리가 아닌 경우
        free(full_path);
        return;
    }

    // 파일 생성 및 쓰기 (O_CREAT | O_WRONLY | O_TRUNC 플래그 사용)
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
    
    // 파일 권한이 0600이 아닌 경우 명시적으로 설정
    if (written == (ssize_t)content_len) {
        chmod(full_path, 0600);
    }
    
    free(full_path);
}