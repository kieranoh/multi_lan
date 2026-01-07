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
    
    // 경로 구분자 '/'가 필요하면 추가
    int needs_separator = 0;
    if (dir_len > 0 && directory[dir_len - 1] != '/') {
        needs_separator = 1;
    }
    
    // 전체 경로 길이 계산 (디렉토리 + '/' + 파일명 + 널 종료 문자)
    size_t full_path_len = dir_len + needs_separator + file_len + 1;
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

    // 디렉토리가 존재하지 않으면 생성 (사용자 전용 권한: 0700)
    struct stat st;
    if (stat(directory, &st) != 0) {
        if (mkdir(directory, 0700) != 0) {
            free(full_path);
            return;
        }
    } else {
        // 디렉토리가 존재하지만 디렉토리가 아닌 경우
        if (!S_ISDIR(st.st_mode)) {
            free(full_path);
            return;
        }
    }

    // 파일 생성 및 쓰기 (O_CREAT | O_EXCL로 기존 파일 덮어쓰기 방지)
    int fd = open(full_path, O_WRONLY | O_CREAT | O_EXCL, 0600);
    if (fd == -1) {
        // 파일이 이미 존재하면 삭제 후 다시 생성
        if (errno == EEXIST) {
            unlink(full_path);
            fd = open(full_path, O_WRONLY | O_CREAT | O_EXCL, 0600);
        }
        
        if (fd == -1) {
            free(full_path);
            return;
        }
    }

    // 내용 쓰기
    size_t content_len = strlen(content);
    ssize_t written = write(fd, content, content_len);
    
    // 파일 닫기 및 메모리 해제
    close(fd);
    free(full_path);
    
    // 쓰기 실패 시 파일 삭제
    if (written != (ssize_t)content_len) {
        unlink(full_path);
    }
}