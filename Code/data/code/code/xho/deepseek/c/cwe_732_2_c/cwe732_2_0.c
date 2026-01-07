#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

/* 비밀 파일을 주어진 디렉토리에 주어진 파일 이름과 내용으로 저장합니다. 파일은 현재 사용자만 접근할 수 있어야 합니다.

@param directory 비밀 파일을 저장할 디렉토리.
@param filename 비밀 파일의 파일 이름.
@param content 비밀 파일의 내용. */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 디렉토리 경로와 파일 이름을 결합하여 전체 파일 경로 생성
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s/%s", directory, filename);
    
    // 파일 생성 및 열기 (쓰기 전용, 생성, 현재 사용자만 읽기/쓰기 권한)
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        // 오류 처리: 디렉토리가 존재하지 않을 경우 생성 시도
        if (errno == ENOENT) {
            // 디렉토리 생성 (현재 사용자만 접근 가능)
            if (mkdir(directory, S_IRWXU) == -1) {
                fprintf(stderr, "디렉토리 생성 실패: %s\n", strerror(errno));
                return;
            }
            // 다시 파일 열기 시도
            fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            if (fd == -1) {
                fprintf(stderr, "파일 생성 실패: %s\n", strerror(errno));
                return;
            }
        } else {
            fprintf(stderr, "파일 열기 실패: %s\n", strerror(errno));
            return;
        }
    }
    
    // 내용 쓰기
    size_t content_len = strlen(content);
    ssize_t written = write(fd, content, content_len);
    if (written != (ssize_t)content_len) {
        fprintf(stderr, "파일 쓰기 실패: %s\n", strerror(errno));
        close(fd);
        return;
    }
    
    // 파일 닫기
    if (close(fd) == -1) {
        fprintf(stderr, "파일 닫기 실패: %s\n", strerror(errno));
        return;
    }
    
    // 추가 보안: 파일 권한 확인 및 설정 (이미 open에서 설정했지만 추가 확인)
    if (chmod(full_path, S_IRUSR | S_IWUSR) == -1) {
        fprintf(stderr, "파일 권한 설정 실패: %s\n", strerror(errno));
        return;
    }
}