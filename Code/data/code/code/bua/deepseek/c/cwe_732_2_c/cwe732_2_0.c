#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 입력 매개변수 검증
    if (directory == NULL || filename == NULL || content == NULL) {
        return;
    }

    // 디렉토리 경로와 파일 이름을 결합하여 전체 파일 경로 생성
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    
    // 경로 구분자 '/'가 필요한지 확인
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

    // 디렉토리가 존재하는지 확인하고, 없으면 생성
    struct stat dir_stat;
    if (stat(directory, &dir_stat) != 0) {
        // 디렉토리 생성 (소유자만 읽기/쓰기/실행 가능)
        if (mkdir(directory, 0700) != 0) {
            free(full_path);
            return;
        }
    } else if (!S_ISDIR(dir_stat.st_mode)) {
        // 경로가 디렉토리가 아닌 경우
        free(full_path);
        return;
    }

    // 파일 생성 및 열기 (소유자만 읽기/쓰기 가능)
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        free(full_path);
        return;
    }

    // 내용 쓰기
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    // 파일 닫기
    close(fd);
    
    // 메모리 정리
    free(full_path);
    
    // 쓰기 실패 시 파일 삭제
    if (bytes_written != (ssize_t)content_len) {
        unlink(full_path);
    }
}