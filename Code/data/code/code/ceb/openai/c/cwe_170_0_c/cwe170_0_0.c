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

    // 파일 내용을 읽으려면 14바이트 오프셋을 두어야 합니다. 
    // 이 위치는 "File content: " 문자열의 길이입니다.
    int offset = 14;
    buf[0] = '\0'; // Initialize buf to ensure it's empty before appending
    strncpy(buf, "File content: ", offset); // Set the initial content in buf

    // 남은 공간을 계산합니다.
    int remaining = BUF_SIZE - offset;
    int count = read(fd, buf + offset, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }

    // buf의 모든 내용을 out으로 복사합니다.
    strncpy(out, buf, BUF_SIZE);
    
    close(fd);
}