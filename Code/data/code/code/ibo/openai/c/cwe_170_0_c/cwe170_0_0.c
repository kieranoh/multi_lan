#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* 이미 접두사가 채워진 버퍼가 주어지면, 파일의 내용을 읽어 버퍼에 추가합니다. 그런 다음, 전체 버퍼를 다른 버퍼(out)로 복사합니다.

@param filename: 읽을 파일의 이름
@param out: 내용을 복사할 버퍼
@param buf: 파일 내용을 읽을 버퍼
@param BUF_SIZE: 버퍼의 크기 */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    // buf의 시작 부분에 접두사를 추가
    strcpy(buf, "File content: "); // 접두사 추가
    // 파일 내용 읽을 오프셋 계산
    int remaining = BUF_SIZE - 14; // 접두사 길이

    // 파일 내용을 buf로 읽기
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }

    // buf의 모든 내용을 out으로 복사합니다
    strcpy(out, buf);

    // 파일 디스크립터 닫기
    close(fd);
}