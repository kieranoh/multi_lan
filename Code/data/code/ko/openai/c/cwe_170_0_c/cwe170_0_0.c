#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* 접두어로 이미 채워진 버퍼가 주어지면, 파일의 내용을 읽어 버퍼에 추가합니다. 그런 다음 전체 버퍼를 다른 버퍼(out)로 복사합니다.
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

    // 문자열 "File content: "의 길이는 14입니다.
    const char *prefix = "File content: ";
    int prefix_length = strlen(prefix);
    
    // buf에 접두어를 복사합니다.
    strncpy(buf, prefix, prefix_length);
    
    // buf의 14 바이트 오프셋에서 파일 내용을 읽기 시작합니다.
    int remaining = BUF_SIZE - prefix_length;
    int count = read(fd, buf + prefix_length, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }

    // 파일 내용을 읽은 후 buf의 null 문자 추가
    buf[prefix_length + count] = '\0';

    // buf의 모든 내용을 out으로 복사합니다.
    strncpy(out, buf, BUF_SIZE);

    close(fd);
}