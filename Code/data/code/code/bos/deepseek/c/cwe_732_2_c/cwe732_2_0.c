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
        fprintf(stderr, "Error: Invalid input parameters\n");
        return;
    }

    // 디렉토리 경로 생성
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    size_t path_len = dir_len + file_len + 2; // '/' + null terminator
    
    char *filepath = (char *)malloc(path_len);
    if (filepath == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return;
    }
    
    // 파일 경로 구성
    snprintf(filepath, path_len, "%s/%s", directory, filename);
    
    // 디렉토리 존재 확인 및 생성 (필요한 경우)
    struct stat dir_stat;
    if (stat(directory, &dir_stat) != 0) {
        // 디렉토리 생성 (700 권한: 사용자만 읽기/쓰기/실행 가능)
        if (mkdir(directory, S_IRWXU) != 0) {
            fprintf(stderr, "Error: Failed to create directory '%s': %s\n", 
                    directory, strerror(errno));
            free(filepath);
            return;
        }
    } else {
        // 디렉토리가 존재하지만 디렉토리인지 확인
        if (!S_ISDIR(dir_stat.st_mode)) {
            fprintf(stderr, "Error: '%s' is not a directory\n", directory);
            free(filepath);
            return;
        }
    }
    
    // 파일 열기 (쓰기 전용, 생성, 존재하면 잘라내기)
    // 600 권한: 사용자만 읽기/쓰기 가능
    int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        fprintf(stderr, "Error: Failed to open file '%s': %s\n", 
                filepath, strerror(errno));
        free(filepath);
        return;
    }
    
    // 내용 쓰기
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written == -1) {
        fprintf(stderr, "Error: Failed to write to file '%s': %s\n", 
                filepath, strerror(errno));
    } else if ((size_t)bytes_written != content_len) {
        fprintf(stderr, "Error: Partial write to file '%s' (%zd of %zu bytes)\n", 
                filepath, bytes_written, content_len);
    }
    
    // 파일 닫기
    if (close(fd) != 0) {
        fprintf(stderr, "Warning: Failed to close file '%s': %s\n", 
                filepath, strerror(errno));
    }
    
    // 메모리 정리
    free(filepath);
}